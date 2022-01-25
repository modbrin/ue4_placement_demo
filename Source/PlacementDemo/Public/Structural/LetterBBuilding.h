// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structural/StaticEntity.h"
#include "LetterBBuilding.generated.h"

/**
 * 
 */
UCLASS()
class PLACEMENTDEMO_API ALetterBBuilding : public AStaticEntity
{
	GENERATED_BODY()
public:
	virtual FText GetDisplayName() const override;
};
