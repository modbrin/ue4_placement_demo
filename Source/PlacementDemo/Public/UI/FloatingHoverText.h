// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FloatingHoverText.generated.h"

/**
 * 
 */
UCLASS()
class PLACEMENTDEMO_API UFloatingHoverText : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* FloatingContainer;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* FloatingText;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* IntegrityProgressBar;

	void SetText(FText Text);
	void SetVisible(bool IsVisible);
};
