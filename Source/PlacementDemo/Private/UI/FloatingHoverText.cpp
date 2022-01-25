// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FloatingHoverText.h"

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UFloatingHoverText::SetText(FText Text)
{
	if (FloatingText != nullptr)
	{
		FloatingText->SetText(Text);
	}
}

void UFloatingHoverText::SetVisible(bool IsVisible)
{
	if (FloatingContainer != nullptr)
	{
		FloatingContainer->SetVisibility(IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}
}
