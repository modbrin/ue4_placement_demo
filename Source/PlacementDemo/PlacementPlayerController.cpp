// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementPlayerController.h"

#include "DrawDebugHelpers.h"
#include "InGameUI.h"
#include "PlacementDemoGameInstance.h"
#include "PlacementPawn.h"
#include "PlacementPreview.h"
#include "Blueprint/UserWidget.h"

APlacementPlayerController::APlacementPlayerController()
{
	BaseZoomRate = 70.f;
	BaseLookUpRate = 2.f;
	BaseTurnRate = 1.f;
	MinViewPitchDegrees = -30.f;
	MaxViewPitchDegrees = 50.f;
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
		PerformObjectPlacement();
	}
}

TOptional<FVector> APlacementPlayerController::TraceMouseLocationToActor(FName Tag) const
{
	FVector CursorLocation;
	FVector CursorDirection;
	DeprojectMousePositionToWorld(CursorLocation, CursorDirection);
	FVector EndTrace = CursorLocation + CursorDirection * 10000.0f;
	
	FHitResult OutHit(ForceInit);
	UWorld* World = GetWorld();

	FCollisionQueryParams CollisionParams;
	const FName TraceTag("PlacementPreviewTraceTag");
	World->DebugDrawTraceTag = TraceTag;
	CollisionParams.TraceTag = TraceTag;
	
	FCollisionObjectQueryParams CollisionObjectParams;
	CollisionObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	
	World->LineTraceSingleByObjectType(OutHit, CursorLocation, EndTrace, CollisionObjectParams, CollisionParams);

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
		// bIsPlacementActive = Enabled;
		if (Enabled)
		{
			if (PlacementActorClass != nullptr && SelectedPlacementActor == nullptr)
			{
				FVector StartingPoint = TraceMouseLocationToActor(TEXT("Ground")).Get(FVector());
				SelectedPlacementActor = World->SpawnActor(PlacementActorClass, &StartingPoint);
				bIsPlacementActive = true;
			}
		}
		else
		{
			if (SelectedPlacementActor != nullptr)
			{
				SelectedPlacementActor->Destroy();
				SelectedPlacementActor = nullptr;
				bIsPlacementActive = false;
			}
		}
	}
	
}

void APlacementPlayerController::PerformObjectPlacement()
{
	TOptional<FVector> TracePoint = TraceMouseLocationToActor(TEXT("Ground"));

	if (SelectedPlacementActor != nullptr)
	{
		APlacementPreview* Actor = Cast<APlacementPreview>(SelectedPlacementActor); // TODO: decide correct way to set visibility
		if (TracePoint.IsSet())
		{
			SelectedPlacementActor->SetActorLocation(TracePoint.GetValue());
			if (Actor != nullptr && Actor->Mesh != nullptr)
			{
				Actor->Mesh->SetVisibility(true);
			}
		}
		else
		{
			if (Actor != nullptr && Actor->Mesh != nullptr)
			{
				Actor->Mesh->SetVisibility(false);
			}
		}
	}
}

void APlacementPlayerController::FinalizePlacement()
{
	if (!bIsPlacementActive) return;
	
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		if (PlacementActorClass != nullptr)
		{
			TOptional<FVector> TargetPoint = TraceMouseLocationToActor(TEXT("Ground"));
			if (TargetPoint.IsSet())
			{
				World->SpawnActor(PlacementActorClass, &TargetPoint.GetValue());
				SetPlacementMode(false);
			}
		}
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