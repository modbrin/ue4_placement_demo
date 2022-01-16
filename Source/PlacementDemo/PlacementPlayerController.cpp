// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementPlayerController.h"

#include "DrawDebugHelpers.h"
#include "PlacementPawn.h"
#include "Blueprint/WidgetLayoutLibrary.h"

APlacementPlayerController::APlacementPlayerController()
{
	BaseZoomRate = 70.f;
	BaseLookUpRate = 1.f;
	BaseTurnRate = 1.f;
}

void APlacementPlayerController::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT(__FUNCTION__));

	Super::BeginPlay();

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetShowMouseCursor(true);
	SetInputMode(InputMode);
}

void APlacementPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction<FCustomInputDelegate>("SetViewMovement", IE_Pressed, this, &APlacementPlayerController::SetViewMovement, true);
	InputComponent->BindAction<FCustomInputDelegate>("SetViewMovement", IE_Released, this, &APlacementPlayerController::SetViewMovement, false);
	InputComponent->BindAction<FCustomInputDelegate>("SetViewOrbiting", IE_Pressed, this, &APlacementPlayerController::SetViewOrbiting, true);
	InputComponent->BindAction<FCustomInputDelegate>("SetViewOrbiting", IE_Released, this, &APlacementPlayerController::SetViewOrbiting, false);
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
}

void APlacementPlayerController::TraceMouseLocation()
{
	FVector CursorLocation;
	FVector CursorDirection;
	DeprojectMousePositionToWorld(CursorLocation, CursorDirection);

	FVector EndTrace = CursorLocation + CursorDirection * 10000.0f;
	
	FHitResult OutHit(ForceInit);
	UWorld* World = GetWorld();
	
	const FName TraceTag("MyTraceTag");
	World->DebugDrawTraceTag = TraceTag;
	FCollisionQueryParams CollisionParams;
	CollisionParams.TraceTag = TraceTag;
	
	World->LineTraceSingleByChannel(OutHit, CursorLocation, EndTrace, ECollisionChannel::ECC_WorldStatic, CollisionParams);
	// World->LineTraceSingleByObjectType()
	
	AActor* HitActor = OutHit.GetActor();
	if (HitActor != nullptr)
	{
		LastGroundTraceLocation.Emplace(OutHit.Location);
	}
	else
	{
		LastGroundTraceLocation.Reset();
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

void APlacementPlayerController::LookUp(float Rate)
{
	if (bIsViewOrbitingActive)
	{
		AddPitchInput(Rate * BaseLookUpRate);
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