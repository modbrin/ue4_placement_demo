// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemPalette.h"
#include "PlacementPreview.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/PaletteActionsHandler.h"
#include "PlacementPlayerController.generated.h"


DECLARE_DELEGATE_OneParam(FCustomInputDelegate, const bool);
/**
 * 
 */
UCLASS()
class PLACEMENTDEMO_API APlacementPlayerController : public APlayerController, public IPaletteActionsHandler
{
	GENERATED_BODY()
public: // methods
	APlacementPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	void LookUp(float Rate);
	void Turn(float Rate);
	void Zoom(float Rate);
	TOptional<FVector> TraceMouseLocationToActor(FName Tag) const;
	TOptional<FVector> TraceMouseLocationOnGroundPlane(float AcceptableTraceDistance = 10000.f) const;
	void PerformViewMovement();
	void SetViewMovement(bool Enabled);
	void SetViewOrbiting(bool Enabled);
	void SetPlacementMode(bool Enabled);
	void PerformPlacementPreview();
	void FinalizePlacement();
	virtual void PaletteItemSelected(const UPaletteEntry* Entry) override;

public: // properties
	TOptional<FVector> GroundPointBeforeMovement{};
	TOptional<FVector> LastGroundTraceLocation{};
	TOptional<FRotator> RotationBeforeOrbiting{};
	FVector2D MousePositionBeforeMovement{};
	FVector PawnLocationBeforeMovement{};
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	bool bIsViewMovementActive = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	bool bIsViewOrbitingActive = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	bool bIsPlacementActive = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Camera)
	float BaseZoomRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Camera)
	float MinViewPitchDegrees;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Camera)
	float MaxViewPitchDegrees;

	TSubclassOf<AMapEntity> PlacementActorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PlacementPreview)
	TSubclassOf<APlacementPreview> PlacementPreviewActorClass;
	
	UStaticMesh* PlacementPreviewMesh;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=PlacementPreview)
	APlacementPreview* PlacementPreviewActor;
};
