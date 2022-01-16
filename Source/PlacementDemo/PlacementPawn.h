// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Zoomable.h"
#include "GameFramework/Pawn.h"
#include "PlacementPawn.generated.h"

UCLASS()
class PLACEMENTDEMO_API APlacementPawn : public APawn, public IZoomable
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlacementPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	// methods
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public: // interface methods
	virtual void Zoom(float Rate) override;
	
public: // properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* TopdownCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinZoomDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxZoomDistance;
};
