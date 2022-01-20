// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapEntity.generated.h"

/**
 * MapEntity is a stationary element of map, can be placed from ItemPalette. Can be constructed, modified and destroyed
 * but can not move by itself.
 */
UCLASS()
class PLACEMENTDEMO_API AMapEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
