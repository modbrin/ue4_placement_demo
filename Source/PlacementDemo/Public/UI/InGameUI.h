// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structural/MapEntity.h"
#include "InGameUI.generated.h"

/**
 * Main UI class that's mostly utilized during gameplay.
 */
UCLASS()
class PLACEMENTDEMO_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetSelectedIntegrity();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetSelectedNextUnitProgress();

	UFUNCTION()
	void DestroySelectionClicked();
	
	void SetSelectionInfoVisibility(bool IsVisible);
	void SetSelectionInfoTitle(FText Text);
	void SetSelectedEntity(AMapEntity* MapEntity);
	void ResetSelection();

public: // properties
	UPROPERTY(meta = (BindWidget))
	class UListView* PaletteListView;

	UPROPERTY(meta = (BindWidget))
	class UBorder* SelectedInfoBorder;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SelectionTitleText;
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* SelectionIntegrityProgress;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* SelectionNextUnitProgress;

	UPROPERTY(meta = (BindWidget))
	class UButton* SelectedEntityDestroyButton;

	TWeakObjectPtr<AMapEntity> SelectedEntity;
};
