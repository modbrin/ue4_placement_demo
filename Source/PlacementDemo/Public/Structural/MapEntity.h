// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapEntity.generated.h"

USTRUCT(BlueprintType)
struct FMapIndex
{
	GENERATED_BODY()
	
	int X, Y;
	FMapIndex(): X(0), Y(0) {}
	FMapIndex(int inX, int inY): X(inX), Y(inY) {}
};

/**
 * MapEntity is a stationary element of map, can be placed from ItemPalette. Can be constructed, modified and destroyed
 * but can not move by itself.
 */
UCLASS()
class PLACEMENTDEMO_API AMapEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	AMapEntity();

protected:
	virtual void BeginPlay() override;

public: // methods
	virtual void Tick(float DeltaTime) override;
	virtual void OnPlaced(FMapIndex placedAt);
	virtual void OnRemoved() {}

	FORCEINLINE FMapIndex GetMapIndex() const
	{
		return MapIndex;
	}
private: // properties
	FMapIndex MapIndex;
};
