// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementPreview.h"

#include "Components/DecalComponent.h"

// Sets default values
APlacementPreview::APlacementPreview(const FObjectInitializer& OI) : Super(OI)
{
	PrimaryActorTick.bCanEverTick = false;
	Mesh = OI.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	SetRootComponent(Mesh);

	PlacementValidationDecal = CreateDefaultSubobject<UDecalComponent>(TEXT("PlacementValidationDecal"));
	PlacementValidationDecal->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	PlacementValidationDecal->DecalSize = FVector(100.f, 100.f, 300.f);
	PlacementValidationDecal->SetRelativeLocation(FVector(0.f, 0.f, 140.f));
	PlacementValidationDecal->SetVisibility(false);
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

void APlacementPreview::ShowInvalidPlacement(bool Enabled)
{
	PlacementValidationDecal->SetVisibility(Enabled);
	Mesh->SetVisibility(!Enabled);
}

void APlacementPreview::SetVisible(bool IsVisible)
{
	GetRootComponent()->SetVisibility(IsVisible, true);
}

