// Fill out your copyright notice in the Description page of Project Settings.


#include "Structural/BasicWall.h"
#include "PlacementDemoGameInstance.h"
#include "Misc/PDUtils.h"

ABasicWall::ABasicWall()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	ConnectorMeshXPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConnectorMeshXPos"));
	ConnectorMeshYPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConnectorMeshYPos"));
	BaseMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ConnectorMeshXPos->AttachToComponent(BaseMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ConnectorMeshYPos->AttachToComponent(BaseMesh, FAttachmentTransformRules::KeepRelativeTransform);
	ConnectorMeshXPos->SetVisibility(false);
	ConnectorMeshYPos->SetVisibility(false);
	ConnectorMeshYPos->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
}

void ABasicWall::BeginPlay()
{
	Super::BeginPlay();
}

FText ABasicWall::GetDisplayName() const
{
	return FText::FromString(TEXT("Basic Wall"));
}

void ABasicWall::InvokeUpdateAdjacent()
{
	UPlacementDemoGameInstance* GI = Cast<UPlacementDemoGameInstance>(GetGameInstance());
	if (GI != nullptr)
	{
		auto CallUpdate = [](TOptional<AMapEntity*> Entity)
		{
			if (Entity.IsSet() && Entity.GetValue() != nullptr)
			{
				// TODO: does it make sense to use APositionalEntity* instead?
				ABasicWall* Wall = Cast<ABasicWall>(Entity.GetValue());
				if (Wall != nullptr)
				{
					Wall->UpdateLook();
				}
			}
		};
		TOptional<AMapEntity*> AdjacentXNeg = GI->GetAdjacentXNeg(GetMapIndex());
		TOptional<AMapEntity*> AdjacentYNeg = GI->GetAdjacentYNeg(GetMapIndex());
		CallUpdate(AdjacentXNeg);
		CallUpdate(AdjacentYNeg);
	}
}

void ABasicWall::OnPlaced(FMapIndex placedAt)
{
	Super::OnPlaced(placedAt);
	
	UpdateLook();
	InvokeUpdateAdjacent();
}

void ABasicWall::UpdateLook()
{
	Super::UpdateLook();

	UPlacementDemoGameInstance* GI = Cast<UPlacementDemoGameInstance>(GetGameInstance());
	if (GI != nullptr)
	{
		auto IsBasicWall = [](TOptional<AMapEntity*> Entity) -> bool
		{
			if (Entity.IsSet() && Entity.GetValue() != nullptr)
			{
				ABasicWall* Wall = Cast<ABasicWall>(Entity.GetValue());
				return Wall != nullptr;
			}
			return false;
		};
		TOptional<AMapEntity*> AdjacentXPos = GI->GetAdjacentXPos(GetMapIndex());
		TOptional<AMapEntity*> AdjacentYPos = GI->GetAdjacentYPos(GetMapIndex());
		ConnectorMeshXPos->SetVisibility(IsBasicWall(AdjacentXPos));
		ConnectorMeshYPos->SetVisibility(IsBasicWall(AdjacentYPos));
	}
}

void ABasicWall::OnCleanupBeforeRemoval()
{
	Super::OnCleanupBeforeRemoval();
	// After reference has been cleared in grid map, update for adjacent is needed
	InvokeUpdateAdjacent();
}

void ABasicWall::OnHoverBegin()
{
	Super::OnHoverBegin();

	if (!bIsSelected)
	{
		BaseMesh->SetRenderCustomDepth(true);
		BaseMesh->SetCustomDepthStencilValue(OUTLINE_COLOR_ORANGE);
		// ConnectorMeshXPos->SetRenderCustomDepth(true);
		// ConnectorMeshXPos->SetCustomDepthStencilValue(OUTLINE_COLOR_ORANGE);
		// ConnectorMeshYPos->SetRenderCustomDepth(true);
		// ConnectorMeshYPos->SetCustomDepthStencilValue(OUTLINE_COLOR_ORANGE);
	}
}

void ABasicWall::OnHoverEnd()
{
	if (bIsHovered)
	{
		BaseMesh->SetRenderCustomDepth(false);
		// ConnectorMeshXPos->SetRenderCustomDepth(false);
		// ConnectorMeshYPos->SetRenderCustomDepth(false);
	}
	Super::OnHoverEnd();
}

void ABasicWall::OnSelected()
{
	Super::OnSelected();
	BaseMesh->SetCustomDepthStencilValue(OUTLINE_COLOR_BLUE);
	BaseMesh->SetRenderCustomDepth(true);
}

void ABasicWall::OnDeselected()
{
	if (bIsSelected)
	{
		BaseMesh->SetRenderCustomDepth(false);
	}
	Super::OnDeselected();
}
