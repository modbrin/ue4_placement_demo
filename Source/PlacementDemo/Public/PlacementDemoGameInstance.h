// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemPalette.h"
#include "Engine/GameInstance.h"
#include "PlacementDemoGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLACEMENTDEMO_API UPlacementDemoGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPlacementDemoGameInstance();

	FORCEINLINE class UInGameUI* GetInGameUI() const { return InGameUI; }

	UFUNCTION(BlueprintCallable)
	void LoadUI();

protected:
	TSubclassOf<UUserWidget> InGameUIClass;

	UPROPERTY(BlueprintReadWrite, Category=UI)
	UInGameUI* InGameUI;

public:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category=Inventory)
	UItemPalette* ItemPalette;
};
