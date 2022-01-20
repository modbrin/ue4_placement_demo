// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaletteEntry.h"
#include "UObject/NoExportTypes.h"
#include "PaletteCategory.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew, BlueprintType)
class PLACEMENTDEMO_API UPaletteCategory : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite)
	TArray<UPaletteEntry*> Entries;
};
