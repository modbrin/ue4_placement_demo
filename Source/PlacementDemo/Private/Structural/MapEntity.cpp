// Fill out your copyright notice in the Description page of Project Settings.


#include "Structural/MapEntity.h"

// Sets default values
AMapEntity::AMapEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapEntity::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMapEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapEntity::OnPlaced(FMapIndex placedAt)
{
	MapIndex = placedAt;
}

