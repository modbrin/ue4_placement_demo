// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structural/MapEntity.h"
#include "UObject/NoExportTypes.h"
#include "PaletteEntry.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew, BlueprintType)
class PLACEMENTDEMO_API UPaletteEntry : public UObject
{
	GENERATED_BODY()
public:
	// Actor name for UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;
	
	// Actor that will be spawned on successful placement
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMapEntity> MapEntityClass;

	// Represents item in UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	// Additional icon for handing mouse hover.
	UPROPERTY(EditAnywhere, blueprintReadWrite)
	UTexture2D* IconHover;

	// Mesh used during placement
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* PreviewMesh;

	// Available for player or not
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsUnlocked;
};
