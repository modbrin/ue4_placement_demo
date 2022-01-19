// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InGameMenuInterface.h"
#include "Engine/GameInstance.h"
#include "PlacementDemoGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLACEMENTDEMO_API UPlacementDemoGameInstance : public UGameInstance, public IInGameMenuInterface
{
	GENERATED_BODY()
protected:
	TSubclassOf<class UUserWidget> InGameUIClass;

	UPROPERTY(BlueprintReadWrite, Category=UI)
	class UInGameUI* InGameUI;
public:
	UPlacementDemoGameInstance(const FObjectInitializer& ObjectInitializer);

	FORCEINLINE class UInGameUI* GetInGameUI() const { return InGameUI; }
	virtual void LoadInGameUI() override;
	virtual void OnLoadInGameMenu_Implementation() override;
};
