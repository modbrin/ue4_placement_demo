// Fill out your copyright notice in the Description page of Project Settings.


#include "Structural/StaticEntity.h"
#include "Misc/PDUtils.h"

AStaticEntity::AStaticEntity(const FObjectInitializer& OI) : Super(OI)
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetCollisionObjectType(ECC_SelectableEntity);
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AStaticEntity::OnHoverBegin()
{
	Super::OnHoverBegin();
	Mesh->SetCustomDepthStencilValue(OUTLINE_COLOR_ORANGE);
	Mesh->SetRenderCustomDepth(true);
}

void AStaticEntity::OnHoverEnd()
{
	Super::OnHoverEnd();
	Mesh->SetRenderCustomDepth(false);
}

FText AStaticEntity::GetDisplayName() const
{
	return FText::FromString(TEXT("Static Entity"));
}
