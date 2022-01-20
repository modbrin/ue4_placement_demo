// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PaletteListEntry.h"
#include "PlacementPlayerController.h"
#include "Components/Button.h"
#include "UI/PaletteEntry.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"

void UPaletteListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	EntryData = Cast<UPaletteEntry>(ListItemObject);
	if (EntryData != nullptr && PaletteItemButton != nullptr)
	{
		FButtonStyle ButtonStyle;
		FSlateBrush NormalBrush = UWidgetBlueprintLibrary::MakeBrushFromTexture(EntryData->Icon);
		ButtonStyle.SetNormal(NormalBrush);
		ButtonStyle.SetHovered(NormalBrush);
		ButtonStyle.SetPressed(NormalBrush);
		ButtonStyle.SetDisabled(NormalBrush);
		PaletteItemButton->SetStyle(ButtonStyle);

		PaletteItemButton->OnClicked.AddDynamic(this, &UPaletteListEntry::HandleClicked);
	}
}

void UPaletteListEntry::HandleClicked()
{
	if (EntryData != nullptr)
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			IPaletteActionsHandler* Handler = Cast<IPaletteActionsHandler>(UGameplayStatics::GetPlayerController(World, 0));
			if (Handler != nullptr)
			{
				Handler->PaletteItemSelected(EntryData);
			}
		}
	}
}
