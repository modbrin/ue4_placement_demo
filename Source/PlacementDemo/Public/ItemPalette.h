// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PaletteCategory.h"
#include "UObject/NoExportTypes.h"
#include "ItemPalette.generated.h"

UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew, BlueprintType)
class PLACEMENTDEMO_API UItemPalette : public UObject
{
	GENERATED_BODY()
public:
	
	// All possible categories
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite)
	TArray<UPaletteCategory*> Categories;
};
