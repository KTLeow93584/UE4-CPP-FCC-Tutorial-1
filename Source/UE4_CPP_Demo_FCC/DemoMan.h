// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Blueprint/UserWidget.h"

#include "DemoMan.generated.h"

UCLASS()
class UE4_CPP_DEMO_FCC_API ADemoMan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADemoMan();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	void MoveForward(float Axis);
	void MoveRight(float Axis);

	bool bDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Power;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Power_Threshold;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Power_Drain_Rate;

	UPROPERTY(EditAnywhere, Category = "UI HUD")
	TSubclassOf<UUserWidget> Player_Power_Widget_Class;

	UUserWidget* Player_Power_Widget;

	UFUNCTION()
	void OnBeginOverlap(
		class UPrimitiveComponent* HitComp,
		class AActor* OtherActor,class UPrimitiveComponent* OtherHitComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult
	);

	void RestartGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PreInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
