// Fill out your copyright notice in the Description page of Project Settings.


#include "Structural/MapEntity.h"

#include "PlacementDemoGameInstance.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMapEntity::AMapEntity(const FObjectInitializer& OI): Super(OI)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = OI.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	FloatingTextWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	FloatingTextWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	FloatingTextWidgetComponent->AttachToComponent(SceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
	Integrity = 100.f;
}

// Called when the game starts or when spawned
void AMapEntity::BeginPlay()
{
	Super::BeginPlay();
	
	UFloatingHoverText* Widget = Cast<UFloatingHoverText>(FloatingTextWidgetComponent->GetWidget());
	if (Widget != nullptr)
	{
		Widget->SetText(GetDisplayName());
		Widget->SetVisible(false);
	}

	TimeCreated = FDateTime::Now();
}

// Called every frame
void AMapEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMapEntity::OnPlaced(FMapIndex PlacedAt)
{
	MapIndex = PlacedAt;
}

void AMapEntity::RemoveSelfFromGridMap()
{
	UPlacementDemoGameInstance* GI = Cast<UPlacementDemoGameInstance>(GetGameInstance());
	if (GI != nullptr)
	{
		GI->ResetMapElemAt(MapIndex);
	}
}

void AMapEntity::OnRemoved()
{
	OnCleanupBeforeRemoval();
	Destroy();
}

void AMapEntity::OnCleanupBeforeRemoval()
{
	RemoveSelfFromGridMap();
}

void AMapEntity::OnHoverBegin()
{
	if (!bIsSelected)
	{
		UFloatingHoverText* Widget = Cast<UFloatingHoverText>(FloatingTextWidgetComponent->GetWidget());
		if (Widget != nullptr)
		{
			Widget->SetVisible(true);
		}
		bIsHovered = true;
	}
}

void AMapEntity::OnHoverEnd()
{
	if (bIsHovered)
	{
		UFloatingHoverText* Widget = Cast<UFloatingHoverText>(FloatingTextWidgetComponent->GetWidget());
		if (Widget != nullptr)
		{
			Widget->SetVisible(false);
		}
		bIsHovered = false;
	}
}

void AMapEntity::OnSelected()
{
	bIsSelected = true;
	OnHoverEnd();
	
	UFloatingHoverText* Widget = Cast<UFloatingHoverText>(FloatingTextWidgetComponent->GetWidget());
	if (Widget != nullptr)
	{
		Widget->SetVisible(true);
	}
}

void AMapEntity::OnDeselected()
{
	bIsSelected = false;

	UFloatingHoverText* Widget = Cast<UFloatingHoverText>(FloatingTextWidgetComponent->GetWidget());
	if (Widget != nullptr)
	{
		Widget->SetVisible(false);
	}
}

void AMapEntity::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (FloatingTextWidgetClass != nullptr)
	{
		FloatingTextWidgetComponent->SetWidgetClass(FloatingTextWidgetClass);
	}
}

float AMapEntity::GetIntegrity() const
{
	return Integrity;
}

FDateTime AMapEntity::GetTimeCreated() const
{
	return TimeCreated;
}

FText AMapEntity::GetDisplayName() const
{
	return FText::FromString(TEXT("Map Entity"));
}


