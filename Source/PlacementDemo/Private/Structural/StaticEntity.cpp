// Fill out your copyright notice in the Description page of Project Settings.


#include "Structural/StaticEntity.h"

AStaticEntity::AStaticEntity()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}
