// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoMan_GameMode.h"
#include "GameFramework/Actor.h"

ADemoMan_GameMode::ADemoMan_GameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADemoMan_GameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this, &ADemoMan_GameMode::SpawnPlayerRecharge, FMath::RandRange(1.0f, 5.0f), true);
}

void ADemoMan_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADemoMan_GameMode::SpawnPlayerRecharge()
{
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

	GetWorld()->SpawnActor(PlayerRechargePickup, &SpawnPosition, &SpawnRotation);
}
