// Fill out your copyright notice in the Description page of Project Settings.


#include "Ground.h"

#include "PlacementPlayerController.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGround::AGround()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
	Mesh->SetMobility(EComponentMobility::Static);
}

// Called when the game starts or when spawned
void AGround::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh != nullptr)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), nullptr);
		Mesh->SetMaterial(0, DynamicMaterial);
		SetGridEnabled(false);
	}

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		
		APlacementPlayerController* Controller = Cast<APlacementPlayerController>(UGameplayStatics::GetPlayerController(World, 0));
		if (Controller != nullptr)
		{
			Controller->PlacementStateChangedDelegate.AddUObject(this, &AGround::SetGridEnabled);
		}
	}
	
}

// Called every frame
void AGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGround::SetGridEnabled(bool Enabled)
{
	if (DynamicMaterial != nullptr)
	{
		DynamicMaterial->SetScalarParameterValue(TEXT("GridEnabled"), Enabled?1.f:0.f);
	}
}
