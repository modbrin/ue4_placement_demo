// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ground.generated.h"

UCLASS()
class PLACEMENTDEMO_API AGround : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGround();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public: // properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Mesh)
	UStaticMeshComponent* Mesh;

	UFUNCTION()
	void SetGridEnabled(bool Enabled);
	
private:
	UMaterialInstanceDynamic* DynamicMaterial;
};
