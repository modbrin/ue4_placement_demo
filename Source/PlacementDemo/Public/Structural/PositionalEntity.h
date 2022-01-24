// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapEntity.h"
#include "PositionalEntity.generated.h"

/**
 * PositionalEntity is a variant of MapEntity, its mesh adapts to its surrounding MapEntities.
 * Examples: fence, gates, stackable buildings.
 */
UCLASS()
class PLACEMENTDEMO_API APositionalEntity : public AMapEntity
{
	GENERATED_BODY()
public:
	virtual void UpdateLook() {}
};
