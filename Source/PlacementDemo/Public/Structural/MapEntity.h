// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI/FloatingHoverText.h"
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
	AMapEntity(const FObjectInitializer&);

protected:
	virtual void BeginPlay() override;

public: // methods
	virtual void Tick(float DeltaTime) override;
	virtual FText GetDisplayName() const;
	virtual void OnPlaced(FMapIndex PlacedAt);
	void RemoveSelfFromGridMap();
	virtual void OnRemoved();
	virtual void OnCleanupBeforeRemoval();
	virtual void OnHoverBegin();
	virtual void OnHoverEnd();
	virtual void OnSelected();
	virtual void OnDeselected();
	virtual void OnConstruction(const FTransform& Transform) override;
	UFUNCTION(BlueprintGetter)
	float GetIntegrity();

	FORCEINLINE FMapIndex GetMapIndex() const
	{
		return MapIndex;
	}
	
public: // properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=UI)
	class UWidgetComponent* FloatingTextWidgetComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=UI)
	TSubclassOf<UFloatingHoverText> FloatingTextWidgetClass;
protected:
	bool bIsHovered = false;
	bool bIsSelected = false;
private: // properties
	FMapIndex MapIndex;
	// Goes from 0 to 100.
	float Integrity;
};
