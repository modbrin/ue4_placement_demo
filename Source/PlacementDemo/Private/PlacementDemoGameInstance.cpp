// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementDemoGameInstance.h"

#include "UI/InGameUI.h"
#include "Blueprint/UserWidget.h"

UPlacementDemoGameInstance::UPlacementDemoGameInstance()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> InGameUIBPClass(TEXT("WidgetBlueprint'/Game/PlacementDemo/HUD/WBP_InGameUI.WBP_InGameUI_C'"));

	if (InGameUIBPClass.Succeeded())
	{
		InGameUIClass = InGameUIBPClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find UI class."));	
	}

	GridSize = 200.f;
}

void UPlacementDemoGameInstance::LoadUI()
{
	if (InGameUIClass != nullptr)
	{
		InGameUI = CreateWidget<UInGameUI>(this, InGameUIClass);
		if (InGameUI != nullptr)
		{
			InGameUI->AddToViewport();
		}
	}
}

void UPlacementDemoGameInstance::InitializeEmptyMap()
{
	MapEntities.SetNumZeroed(MapXSize * MapYSize);
}

bool UPlacementDemoGameInstance::IsCoordinateInMap(int inX, int inY) const
{
	return inX > 0 && inY > 0 && inX < MapXSize && inY < MapYSize;
}

TOptional<AMapEntity*> UPlacementDemoGameInstance::GetMapElemAt(FMapIndex inCoord) const
{
	if (IsCoordinateInMap(inCoord.X, inCoord.Y))
	{
		AMapEntity* Elem = MapEntities[inCoord.X * MapYSize + inCoord.Y];
		return TOptional<AMapEntity*>(Elem);
	}
	else
	{
		return TOptional<AMapEntity*>();
	}
}

TOptional<AMapEntity*> UPlacementDemoGameInstance::GetMapElemAtLocation(FVector Location) const
{
	FMapIndex MapIndex = ConvertLocationToMapIndex(Location);
	return GetMapElemAt(MapIndex);
}

bool UPlacementDemoGameInstance::SetMapElemAt(FMapIndex inCoord, AMapEntity* MapEntity)
{
	if (IsCoordinateInMap(inCoord.X, inCoord.Y))
	{
		MapEntities[inCoord.X * MapYSize + inCoord.Y] = MapEntity;
		MapEntity->OnPlaced(inCoord);
		return true;
	}
	else
	{
		return false;
	}
}

bool UPlacementDemoGameInstance::SetMapElemAtLocation(FVector Location, AMapEntity* MapEntity)
{
	FMapIndex MapIndex = ConvertLocationToMapIndex(Location);
	return SetMapElemAt(MapIndex, MapEntity);
}

FMapIndex UPlacementDemoGameInstance::ConvertLocationToMapIndex(FVector Location) const
{
	auto ConvertToIndex = [this](float axis) -> int
	{
		return FMath::FloorToInt(axis / GridSize);
	};
	return FMapIndex(ConvertToIndex(Location.X), ConvertToIndex(Location.Y));
}

// TODO: create separate GridMap class
TOptional<AMapEntity*> UPlacementDemoGameInstance::GetAdjacentXPos(FMapIndex fromIndex)
{
	++fromIndex.X;
	return GetMapElemAt(fromIndex);
}

TOptional<AMapEntity*> UPlacementDemoGameInstance::GetAdjacentYPos(FMapIndex fromIndex)
{
	++fromIndex.Y;
	return GetMapElemAt(fromIndex);
}

TOptional<AMapEntity*> UPlacementDemoGameInstance::GetAdjacentXNeg(FMapIndex fromIndex)
{
	--fromIndex.X;
	return GetMapElemAt(fromIndex);
}

TOptional<AMapEntity*> UPlacementDemoGameInstance::GetAdjacentYNeg(FMapIndex fromIndex)
{
	--fromIndex.Y;
	return GetMapElemAt(fromIndex);
}
