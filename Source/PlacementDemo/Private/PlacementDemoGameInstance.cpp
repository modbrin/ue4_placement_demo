// Fill out your copyright notice in the Description page of Project Settings.


#include "PlacementDemoGameInstance.h"

#include "InGameUI.h"
#include "Blueprint/UserWidget.h"

UPlacementDemoGameInstance::UPlacementDemoGameInstance(const FObjectInitializer& Objectinitializer)
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
}

void UPlacementDemoGameInstance::LoadInGameUI()
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

void UPlacementDemoGameInstance::OnLoadInGameMenu_Implementation()
{
	LoadInGameUI();
}