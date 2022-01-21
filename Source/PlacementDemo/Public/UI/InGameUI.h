// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

DECLARE_DELEGATE(FPlacementButtonClickedSignature)

/**
 * 
 */
UCLASS()
class PLACEMENTDEMO_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
public: // properties
	UPROPERTY(meta = (BindWidget))
	class UListView* PaletteListView;

	FPlacementButtonClickedSignature ButtonClickedDelegate;
};
