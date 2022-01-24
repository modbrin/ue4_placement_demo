// Fill out your copyright notice in the Description page of Project Settings.


#include "Structural/BasicWall.h"
#include "PlacementDemoGameInstance.h"

ABasicWall::ABasicWall()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	ConnectorMeshXPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConnectorMeshXPos"));
	ConnectorMeshYPos = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConnectorMeshYPos"));
	SetRootComponent(BaseMesh);
	ConnectorMeshXPos->SetupAttachment(BaseMesh);
	ConnectorMeshYPos->SetupAttachment(BaseMesh);
	ConnectorMeshXPos->SetVisibility(false);
	ConnectorMeshYPos->SetVisibility(false);
	ConnectorMeshYPos->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
}

void ABasicWall::BeginPlay()
{
	Super::BeginPlay();
}

void ABasicWall::OnPlaced(FMapIndex placedAt)
{
	Super::OnPlaced(placedAt);
	
	UpdateLook();
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

void ABasicWall::OnRemoved()
{
	// TODO: handle removal
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

void ABasicWall::OnHoverBegin()
{
	Super::OnHoverBegin();

	BaseMesh->SetRenderCustomDepth(true);
	ConnectorMeshXPos->SetRenderCustomDepth(true);
	ConnectorMeshYPos->SetRenderCustomDepth(true);
}

void ABasicWall::OnHoverEnd()
{
	Super::OnHoverEnd();

	BaseMesh->SetRenderCustomDepth(false);
	ConnectorMeshXPos->SetRenderCustomDepth(false);
	ConnectorMeshYPos->SetRenderCustomDepth(false);
}
