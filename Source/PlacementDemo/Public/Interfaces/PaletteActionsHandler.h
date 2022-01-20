// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/PaletteEntry.h"
#include "UObject/Interface.h"
#include "PaletteActionsHandler.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPaletteActionsHandler : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PLACEMENTDEMO_API IPaletteActionsHandler
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void PaletteItemSelected(const UPaletteEntry* Entry) {}
};
