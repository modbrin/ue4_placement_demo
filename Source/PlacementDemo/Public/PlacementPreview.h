// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlacementPreview.generated.h"

UCLASS()
class PLACEMENTDEMO_API APlacementPreview : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlacementPreview(const FObjectInitializer& OI);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void ShowInvalidPlacement(bool Enabled);
	void SetVisible(bool IsVisible);

public: // properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDecalComponent* PlacementValidationDecal;
};
