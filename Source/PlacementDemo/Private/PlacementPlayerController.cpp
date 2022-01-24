// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementPlayerController.h"

#include "DrawDebugHelpers.h"
#include "UI/InGameUI.h"
#include "PlacementDemoGameInstance.h"
#include "PlacementPawn.h"
#include "PlacementPreview.h"
#include "Blueprint/UserWidget.h"
#include "Misc/PDUtils.h"

APlacementPlayerController::APlacementPlayerController()
{
	BaseZoomRate = 70.f;
	BaseLookUpRate = 2.f;
	BaseTurnRate = 1.f;
	MinViewPitchDegrees = -30.f;
	MaxViewPitchDegrees = 50.f;
	GridSize = 200;
}

void APlacementPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Setup mouse behavior
	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetShowMouseCursor(true);
	SetInputMode(InputMode);


	UPlacementDemoGameInstance* GI = Cast<UPlacementDemoGameInstance>(GetGameInstance());
	if (GI != nullptr)
	{
		UInGameUI* UI = GI->GetInGameUI();
		if (UI != nullptr)
		{
			UI->ButtonClickedDelegate.BindLambda([this]()
			{
				this->SetPlacementMode(true);
			});
		}
	}
}

void APlacementPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction<FCustomInputDelegate>("SetViewMovement", IE_Pressed, this, &APlacementPlayerController::SetViewMovement, true);
	InputComponent->BindAction<FCustomInputDelegate>("SetViewMovement", IE_Released, this, &APlacementPlayerController::SetViewMovement, false);
	InputComponent->BindAction<FCustomInputDelegate>("SetViewOrbiting", IE_Pressed, this, &APlacementPlayerController::SetViewOrbiting, true);
	InputComponent->BindAction<FCustomInputDelegate>("SetViewOrbiting", IE_Released, this, &APlacementPlayerController::SetViewOrbiting, false);
	InputComponent->BindAction<FCustomInputDelegate>("CancelAction", IE_Pressed, this, &APlacementPlayerController::SetPlacementMode, false);
	InputComponent->BindAction("MainAction", IE_Pressed, this, &APlacementPlayerController::FinalizePlacement);

	InputComponent->BindAxis("Turn", this, &APlacementPlayerController::Turn);
	InputComponent->BindAxis("LookUp", this, &APlacementPlayerController::LookUp);
	InputComponent->BindAxis("Zoom", this, &APlacementPlayerController::Zoom);
}

void APlacementPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsViewMovementActive)
	{
		PerformViewMovement();
	}

	if (bIsPlacementActive)
	{
		PerformPlacementPreview();
	}
	else
	{
		PerformHoverTest();
	}
}

TOptional<FVector> APlacementPlayerController::TraceMouseLocationToActor(FName Tag) const
{
	// TODO: rewrite to use collision channel
	
	FVector CursorLocation;
	FVector CursorDirection;
	DeprojectMousePositionToWorld(CursorLocation, CursorDirection);
	FVector EndTrace = CursorLocation + CursorDirection * 10000.0f;
	
	FHitResult OutHit(ForceInit);
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		FCollisionQueryParams CollisionParams;
		const FName TraceTag("PlacementPreviewTraceTag");
		// World->DebugDrawTraceTag = TraceTag;
		CollisionParams.TraceTag = TraceTag;
	
		FCollisionObjectQueryParams CollisionObjectParams;
		CollisionObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	
		World->LineTraceSingleByObjectType(OutHit, CursorLocation, EndTrace, CollisionObjectParams, CollisionParams);
	}

	AActor* HitActor = OutHit.GetActor();
	if (HitActor != nullptr && HitActor->ActorHasTag(Tag))
	{
		return TOptional<FVector>(OutHit.Location);
	}
	else
	{
		return TOptional<FVector>();
	}
}

TOptional<FVector> APlacementPlayerController::TraceMouseLocationOnGroundPlane(float AcceptableTraceDistance) const
{
	FVector MouseLocation, MouseDirection;
	DeprojectMousePositionToWorld(MouseLocation, MouseDirection);
	if (MouseDirection.Z == 0.f)
	{
		return TOptional<FVector>();
	}

	const float T = -MouseLocation.Z / MouseDirection.Z;
	const FVector IntersectionPoint = FVector(MouseLocation.X + MouseDirection.X * T,MouseLocation.Y + MouseDirection.Y * T, 0.f);

	const FVector TraceVector = IntersectionPoint - MouseLocation;
	if (TraceVector.Size() <= AcceptableTraceDistance)
	{
		// DrawDebugLine(GetWorld(), MouseLocation, IntersectionPoint, FColor::Red);
		DrawDebugSphere(GetWorld(), IntersectionPoint, 10.f, 10, FColor::Green);
		return TOptional<FVector>(TraceVector);
	}
	else
	{
		return TOptional<FVector>();
	}
}

TOptional<AMapEntity*> APlacementPlayerController::TraceMouseLocationToSelectableEntity()
{
	FVector CursorLocation;
	FVector CursorDirection;
	DeprojectMousePositionToWorld(CursorLocation, CursorDirection);
	FVector EndTrace = CursorLocation + CursorDirection * 10000.0f;
	
	FHitResult OutHit(ForceInit);
	UWorld* World = GetWorld();

	if (World != nullptr)
	{
		FCollisionQueryParams CollisionParams;
		const FName TraceTag("SelectableEntityTraceTag");
		// World->DebugDrawTraceTag = TraceTag;
		CollisionParams.TraceTag = TraceTag;
		
		World->LineTraceSingleByChannel(OutHit, CursorLocation, EndTrace, ECC_SelectableEntity, CollisionParams);
	}

	AMapEntity* HitActor = Cast<AMapEntity>(OutHit.GetActor());
	if (HitActor != nullptr)
	{
		return TOptional<AMapEntity*>(HitActor);
	}
	else
	{
		return TOptional<AMapEntity*>();
	}
}

void APlacementPlayerController::PerformViewMovement()
{
	TOptional<FVector> CurrentGroundPoint = TraceMouseLocationOnGroundPlane();
		
	if (CurrentGroundPoint.IsSet() && GroundPointBeforeMovement.IsSet())
	{
		FVector CurrentPawnLocation = GetPawn()->GetTransform().GetLocation();
		FVector Offset = CurrentGroundPoint.GetValue() - GroundPointBeforeMovement.GetValue();
		FVector NewPawnLocation = PawnLocationBeforeMovement - Offset;
		GetPawn()->SetActorLocation(FVector(NewPawnLocation.X, NewPawnLocation.Y, CurrentPawnLocation.Z));
	}
}

void APlacementPlayerController::SetViewMovement(bool Enabled)
{
	TOptional<FVector> GroundPoint = TraceMouseLocationOnGroundPlane();
	if (GroundPoint.IsSet())
	{
		bIsViewMovementActive = Enabled;

		if (Enabled)
		{
			GroundPointBeforeMovement = GroundPoint;
			PawnLocationBeforeMovement = GetPawn()->GetTransform().GetLocation();
		}
		else
		{
			GroundPointBeforeMovement.Reset();
		}
	}
}

void APlacementPlayerController::SetViewOrbiting(bool Enabled)
{
	bIsViewOrbitingActive = Enabled;
}

void APlacementPlayerController::SetPlacementMode(bool Enabled)
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		if (Enabled)
		{
			if (PlacementActorClass != nullptr && PlacementPreviewActorClass != nullptr && PlacementPreviewActor == nullptr)
			{
				const FVector StartingPoint = TraceMouseLocationToActor(TEXT("Ground")).Get(FVector());
				AActor* SpawnedActor = World->SpawnActor(PlacementPreviewActorClass, &StartingPoint);
				APlacementPreview* PreviewActor = Cast<APlacementPreview>(SpawnedActor);
				if (PreviewActor != nullptr && PreviewActor->Mesh != nullptr && PlacementPreviewMesh != nullptr)
				{
					PreviewActor->Mesh->SetStaticMesh(PlacementPreviewMesh.Get());
					PlacementPreviewActor = PreviewActor;
					bIsPlacementActive = true;
					PlacementStateChangedDelegate.Broadcast(true);
				}
				else
				{
					SpawnedActor->Destroy();
				}
			}
		}
		else
		{
			if (PlacementPreviewActor != nullptr)
			{
				PlacementPreviewActor->Destroy();
				PlacementPreviewActor = nullptr;
				bIsPlacementActive = false;
				PlacementStateChangedDelegate.Broadcast(false);
			}
		}
	}
	
}

void APlacementPlayerController::PerformPlacementPreview()
{
	TOptional<FVector> TracePoint = TraceMouseLocationToActor(TEXT("Ground"));

	if (PlacementPreviewActor != nullptr && PlacementPreviewActor->Mesh != nullptr)
	{
		if (TracePoint.IsSet())
		{
			PlacementPreviewActor->SetActorLocation(PDUtils::SnapLocationToGrid(TracePoint.GetValue(), GridSize));
			PlacementPreviewActor->Mesh->SetVisibility(true);
		}
		else
		{
			PlacementPreviewActor->Mesh->SetVisibility(false);
		}
	}
}

void APlacementPlayerController::FinalizePlacement()
{
	if (!bIsPlacementActive) return;
	
	UWorld* World = GetWorld();
	UPlacementDemoGameInstance* GI = Cast<UPlacementDemoGameInstance>(GetGameInstance());
	if (World != nullptr && GI != nullptr)
	{
		if (PlacementActorClass != nullptr)
		{
			TOptional<FVector> TargetPoint = TraceMouseLocationToActor(TEXT("Ground"));
			if (TargetPoint.IsSet())
			{
				FVector PlacementLocation = PDUtils::SnapLocationToGrid(TargetPoint.GetValue(), GridSize);
				AActor* PlacedActor = World->SpawnActor(PlacementActorClass, &PlacementLocation);
				AMapEntity* PlacedMapEntity = Cast<AMapEntity>(PlacedActor);
				check(PlacedMapEntity != nullptr);

				bool success = GI->SetMapElemAtLocation(PlacementLocation, PlacedMapEntity);
				SetPlacementMode(false);
			}
		}
	}
}

void APlacementPlayerController::PaletteItemSelected(const UPaletteEntry* Entry)
{
	if (Entry != nullptr && !bIsPlacementActive)
	{
		PlacementActorClass = Entry->MapEntityClass;
		PlacementPreviewMesh = Entry->PreviewMesh;
		SetPlacementMode(true);
	}
}

void APlacementPlayerController::LookUp(float Rate)
{
	if (bIsViewOrbitingActive)
	{
		const FRotator CurrentControlRotation = GetControlRotation();
		float NewPitch = CurrentControlRotation.Pitch + Rate * BaseLookUpRate; 
		NewPitch = FMath::ClampAngle(NewPitch, MinViewPitchDegrees, MaxViewPitchDegrees);
		SetControlRotation(FRotator(NewPitch, CurrentControlRotation.Yaw, CurrentControlRotation.Roll));
	}
}

void APlacementPlayerController::Turn(float Rate)
{
	if (bIsViewOrbitingActive)
	{
		AddYawInput(Rate * BaseTurnRate);
	}
}

void APlacementPlayerController::Zoom(float Rate)
{
	IZoomable* Zoomable = Cast<IZoomable>(GetPawn());
	if (Zoomable)
	{
		Zoomable->Zoom(Rate * BaseZoomRate);
	}
}

void APlacementPlayerController::PerformHoverTest()
{
	TOptional<AMapEntity*> TracedEntity = TraceMouseLocationToSelectableEntity();
	if (TracedEntity.IsSet() && TracedEntity.GetValue() != nullptr)
	{
		if (!LastHoveredMapEntity.IsSet())
		{
			// nothing was selected recently
			TracedEntity.GetValue()->OnHoverBegin();
			LastHoveredMapEntity.Emplace(TracedEntity.GetValue());
		}
		else if (LastHoveredMapEntity.GetValue() != TracedEntity.GetValue())
		{
			// switching between selectable entities seamlessly
			LastHoveredMapEntity.GetValue()->OnHoverEnd();
			TracedEntity.GetValue()->OnHoverBegin();
			LastHoveredMapEntity.Emplace(TracedEntity.GetValue());
		}
	} else if (LastHoveredMapEntity.IsSet() && LastHoveredMapEntity.GetValue() != nullptr)
	{
		// nothing is selected now, need to unselect last item
		LastHoveredMapEntity.GetValue()->OnHoverEnd();
		LastHoveredMapEntity.Reset();
	}
}