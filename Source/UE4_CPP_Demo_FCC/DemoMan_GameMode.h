// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "DemoMan_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class UE4_CPP_DEMO_FCC_API ADemoMan_GameMode : public AGameMode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<APawn> PlayerRechargePickup;

	float Spawn_Z = 500.0f;

	UPROPERTY(EditAnywhere)
	float Spawn_X_Min;

	UPROPERTY(EditAnywhere)
	float Spawn_X_Max;

	UPROPERTY(EditAnywhere)
	float Spawn_Y_Min;

	UPROPERTY(EditAnywhere)
	float Spawn_Y_Max;

	ADemoMan_GameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SpawnPlayerRecharge();
};
