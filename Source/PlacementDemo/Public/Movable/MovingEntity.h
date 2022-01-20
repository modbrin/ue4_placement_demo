// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovingEntity.generated.h"

/**
 * MovingEntity represents NPCs, controlled by AI and cannot be possessed by player.
 * Examples: worker bots, enemies, allies.
 */
UCLASS()
class PLACEMENTDEMO_API AMovingEntity : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovingEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
