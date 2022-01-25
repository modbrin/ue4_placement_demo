// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define ECC_SelectableEntity ECC_GameTraceChannel1

#define OUTLINE_COLOR_GREEN 253
#define OUTLINE_COLOR_ORANGE 252
#define OUTLINE_COLOR_BLUE 251

/**
 * Useful generic functions.
 */
struct PLACEMENTDEMO_API PDUtils
{
    static FVector SnapLocationToGrid(const FVector Location, const int GridSize);
};
