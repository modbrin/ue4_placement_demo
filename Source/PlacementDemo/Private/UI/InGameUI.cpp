// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameUI.h"

#include "PlacementDemoGameInstance.h"
#include "Components/Button.h"
#include "Components/ListView.h"

void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	UPlacementDemoGameInstance* GI = Cast<UPlacementDemoGameInstance>(GetGameInstance());
	if (GI != nullptr)
	{
		if (GI->ItemPalette->Categories.Num() != 0)
		{
			PaletteListView->SetListItems(GI->ItemPalette->Categories[0]->Entries);
		}
	}
}

void UInGameUI::NativeDestruct()
{
	Super::NativeDestruct();
}
