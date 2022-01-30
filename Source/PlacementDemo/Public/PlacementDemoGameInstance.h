// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemPalette.h"
#include "Engine/GameInstance.h"
#include "PlacementDemoGameInstance.generated.h"


UCLASS()
class PLACEMENTDEMO_API UPlacementDemoGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPlacementDemoGameInstance();

	FORCEINLINE class UInGameUI* GetInGameUI() const { return InGameUI; }

	UFUNCTION(BlueprintCallable)
	void LoadUI();

	UFUNCTION(BlueprintCallable)
	void InitializeEmptyMap();
	
	bool IsCoordinateInMap(int inX, int inY) const;
	TOptional<AMapEntity*> GetMapElemAt(FMapIndex inCoord) const;
	TOptional<AMapEntity*> GetMapElemAtLocation(FVector Location) const;
	bool SetMapElemAt(FMapIndex inCoord, AMapEntity* MapEntity);
	bool SetMapElemAtLocation(FVector Location, AMapEntity* MapEntity);
	void ResetMapElemAt(FMapIndex inCoord);
	bool IsCellAvailableAtLocation(FVector Location);
	FMapIndex ConvertLocationToMapIndex(FVector) const;
	TOptional<AMapEntity*> GetAdjacentXPos(FMapIndex fromIndex);
	TOptional<AMapEntity*> GetAdjacentYPos(FMapIndex fromIndex);
	TOptional<AMapEntity*> GetAdjacentXNeg(FMapIndex fromIndex);
	TOptional<AMapEntity*> GetAdjacentYNeg(FMapIndex fromIndex);

protected:
	TSubclassOf<UUserWidget> InGameUIClass;

	UPROPERTY(BlueprintReadWrite, Category=UI)
	UInGameUI* InGameUI;

	UPROPERTY()
	TArray<AMapEntity*> MapEntities;
	
public:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category=Inventory)
	UItemPalette* ItemPalette;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Map)
	int MapXSize;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Map)
	int MapYSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Map)
	int GridSize;
};
