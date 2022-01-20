// Fill out your copyright notice in the Description page of Project Settings.


#include "Movable/MovingEntity.h"

// Sets default values
AMovingEntity::AMovingEntity()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMovingEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

