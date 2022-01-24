// Fill out your copyright notice in the Description page of Project Settings.


#include "Misc/PDUtils.h"

// Snap location to grid according to ground plane (XY), Z axis is unchanged. 
FVector PDUtils::SnapLocationToGrid(const FVector Location, const int GridSize)
{
	auto SnapToGrid = [&](float axis) -> float
	{
		// TODO: is fmod performance ok?
		float axisMod = axis -  FMath::Fmod(axis, static_cast<float>(GridSize));
		if (axis > 0)
		{
			return axisMod + static_cast<float>(GridSize) / 2.f;
		}
		else
		{
			return axisMod - static_cast<float>(GridSize) / 2.f;	
		}
	};
	return FVector(SnapToGrid(Location.X), SnapToGrid(Location.Y), Location.Z);
}
