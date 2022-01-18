// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementPreview.h"

// Sets default values
APlacementPreview::APlacementPreview()
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void APlacementPreview::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlacementPreview::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

