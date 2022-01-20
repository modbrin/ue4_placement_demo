// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameUI.h"

#include "PlacementDemoGameInstance.h"
#include "Components/Button.h"
#include "Components/ListView.h"

void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	ActivatePlacementButton->OnClicked.AddDynamic(this, &UInGameUI::DispatchButtonEvent);
	
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
	ActivatePlacementButton->OnClicked.RemoveDynamic(this, &UInGameUI::DispatchButtonEvent);

	Super::NativeDestruct();
}

void UInGameUI::DispatchButtonEvent()
{
	bool ExecResult = ButtonClickedDelegate.ExecuteIfBound();
}
