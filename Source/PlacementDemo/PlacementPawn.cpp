// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementPawn.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlacementPawn::APlacementPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    TopdownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopdownCamera"));

    SetRootComponent(SceneRoot);
	TopdownCamera->SetupAttachment(RootComponent);
	TopdownCamera->bUsePawnControlRotation = false;

	MinZoomDistance = 100.f;
	MaxZoomDistance = 1000.f;
}

// Called when the game starts or when spawned
void APlacementPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlacementPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlacementPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlacementPawn::Zoom(float Rate)
{
	FVector ForwardVector = TopdownCamera->GetForwardVector();
	FVector CurrentLocation = TopdownCamera->GetRelativeLocation();
	FVector NewLocation = CurrentLocation - CurrentLocation.GetSafeNormal() * Rate;
	TopdownCamera->SetRelativeLocation(NewLocation.GetClampedToSize(MinZoomDistance, MaxZoomDistance));
	
	UE_LOG(LogTemp, Warning, TEXT("Forward: %s, Rate: %f"), *ForwardVector.ToString(), Rate);
}

