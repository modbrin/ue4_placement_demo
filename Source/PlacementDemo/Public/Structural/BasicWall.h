// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structural/PositionalEntity.h"
#include "BasicWall.generated.h"

/**
 * 
 */
UCLASS()
class PLACEMENTDEMO_API ABasicWall : public APositionalEntity
{
	GENERATED_BODY()
public:
	ABasicWall();

	virtual void BeginPlay() override;
	virtual void OnPlaced(FMapIndex placedAt) override;
	virtual void OnRemoved() override;
	virtual void UpdateLook() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ConnectorMeshXPos;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ConnectorMeshYPos;
	
	
};
