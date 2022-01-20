// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "PaletteListEntry.generated.h"

/**
 * 
 */
UCLASS()
class PLACEMENTDEMO_API UPaletteListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
protected:
	// IUserObjectListEntry
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	// IUserObjectListEntry
	
	UPROPERTY(meta=(BindWidget))
	class UButton* PaletteItemButton;

	UPROPERTY()
	class UPaletteEntry* EntryData;;

public:
	UFUNCTION()
	void HandleClicked();
};
