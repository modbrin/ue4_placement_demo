// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * Useful generic functions.
 */
struct PLACEMENTDEMO_API PDUtils
{
    static FVector SnapLocationToGrid(const FVector Location, const int GridSize);
};
