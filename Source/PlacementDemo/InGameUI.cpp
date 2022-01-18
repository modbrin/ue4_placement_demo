// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"

#include "Components/Button.h"

// bool UInGameUI::Initialize()
// {
// 	// ActivatePlacementButton->OnClicked.AddDynamic(this, &UInGameUI::DispatchButtonEvent);
//
// 	return true;
// }

void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();

	ActivatePlacementButton->OnClicked.AddDynamic(this, &UInGameUI::DispatchButtonEvent);
}

void UInGameUI::NativeDestruct()
{
	ActivatePlacementButton->OnClicked.RemoveDynamic(this, &UInGameUI::DispatchButtonEvent);

	Super::NativeDestruct();
}

void UInGameUI::DispatchButtonEvent()
{
	ButtonClickedDelegate.ExecuteIfBound();
}
