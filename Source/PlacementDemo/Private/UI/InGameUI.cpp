// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameUI.h"
#include "PlacementDemoGameInstance.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Interfaces/PaletteActionsHandler.h"
#include "Kismet/GameplayStatics.h"

void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	UPlacementDemoGameInstance* GI = Cast<UPlacementDemoGameInstance>(GetGameInstance());
	if (GI != nullptr)
	{
		if (GI->ItemPalette != nullptr && GI->ItemPalette->Categories.Num() != 0)
		{
			PaletteListView->SetListItems(GI->ItemPalette->Categories[0]->Entries);
		}
		if (SelectedInfoBorder != nullptr)
		{
			// start with info hidden
			SetSelectionInfoVisibility(false);
		}
		if (SelectedEntityDestroyButton != nullptr)
		{
			SelectedEntityDestroyButton->OnClicked.AddDynamic(this, &UInGameUI::DestroySelectionClicked);
		}
	}
}

void UInGameUI::NativeDestruct()
{
	Super::NativeDestruct();
}

float UInGameUI::GetSelectedIntegrity()
{
	if (SelectedEntity.IsValid())
	{
		return SelectedEntity.Get()->GetIntegrity() / 100.f;
	}
	return 0.f;
}

float UInGameUI::GetSelectedNextUnitProgress()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		return FMath::Abs(FMath::Sin(World->GetTimeSeconds()));
	}
	return 0.f;
}

void UInGameUI::SetSelectionInfoVisibility(bool IsVisible)
{
	if (SelectedInfoBorder != nullptr)
	{
		SelectedInfoBorder->SetVisibility(IsVisible?ESlateVisibility::Visible:ESlateVisibility::Collapsed);
	}
}

void UInGameUI::SetSelectionInfoTitle(FText Text)
{
	if (SelectionTitleText != nullptr)
	{
		SelectionTitleText->SetText(Text);
	}
}

void UInGameUI::SetSelectedEntity(AMapEntity* MapEntity)
{
	if (MapEntity != nullptr)
	{
		SelectedEntity = MapEntity;
		SetSelectionInfoTitle(MapEntity->GetDisplayName());
	}
}

void UInGameUI::ResetSelection()
{
	SelectedEntity.Reset();
}

void UInGameUI::DestroySelectionClicked()
{
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		IPaletteActionsHandler* Handler = Cast<IPaletteActionsHandler>(UGameplayStatics::GetPlayerController(World, 0));
		if (Handler != nullptr)
		{
			Handler->DestroySelectedEntityInvoked();
		}
	}
}
