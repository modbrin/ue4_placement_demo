// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapEntity.h"
#include "StaticEntity.generated.h"

/**
 * StaticEntity is a simple variant of MapEntity, represents a simple mesh and primitive logic.
 * Examples: standalone building.
 */
UCLASS()
class PLACEMENTDEMO_API AStaticEntity : public AMapEntity
{
	GENERATED_BODY()
public:
	AStaticEntity();
	
public: // properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
};
