// Fill out your copyright notice in the Description page of Project Settings.


#include "Structural/StaticEntity.h"

#include "PlacementPlayerController.h"

AStaticEntity::AStaticEntity()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetCollisionObjectType(ECC_SelectableEntity);
}

void AStaticEntity::OnHoverBegin()
{
	Super::OnHoverBegin();
	Mesh->SetRenderCustomDepth(true);
}

void AStaticEntity::OnHoverEnd()
{
	Super::OnHoverEnd();
	Mesh->SetRenderCustomDepth(false);
}
