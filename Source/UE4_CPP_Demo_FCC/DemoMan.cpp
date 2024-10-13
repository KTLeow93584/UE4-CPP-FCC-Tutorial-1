// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoMan.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADemoMan::ADemoMan()
{
	// ------------------------
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// ------------------------
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
	// ------------------------
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// ------------------------
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	// ------------------------
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	// ------------------------
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowCamera->bUsePawnControlRotation = false;
	// ------------------------
}

// Called when the game starts or when spawned
void ADemoMan::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADemoMan::OnBeginOverlap);

	if (Player_Power_Widget_Class != nullptr)
	{
		Player_Power_Widget = CreateWidget(GetWorld(), Player_Power_Widget_Class);
		Player_Power_Widget->AddToViewport();
	}
}

void ADemoMan::PreInitializeComponents()
{
	bDead = false;
	Power = Power_Threshold;
}

// Called every frame
void ADemoMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDead)
		return;

	Power -= DeltaTime * Power_Drain_Rate;

	if (Power < 0.0f) {
		Power = 0.0f;
		if (!bDead) {
			bDead = true;
			GetMesh()->SetSimulatePhysics(true);

			// Restart the game
			FTimerHandle UnusedHandle;
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &ADemoMan::RestartGame, 3.0f, false);
		}
	}
}

// Called to bind functionality to input
void ADemoMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADemoMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADemoMan::MoveRight);
}

void ADemoMan::MoveForward(float Axis)
{
	if (bDead)
		return;
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Axis);
}

void ADemoMan::MoveRight(float Axis)
{
	if (bDead)
		return;
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Axis);
}

void ADemoMan::OnBeginOverlap(
	UPrimitiveComponent* HitComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherHitComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
)
{
	if (OtherActor->ActorHasTag("Recharge")) {
		Power += 10.0f;

		if (Power > 100.0f)
			Power = 100.0f;

		OtherActor->Destroy();

		UE_LOG(LogTemp, Warning, TEXT("I have hit a Recharge Ball! Power: %d"), Power);
		UE_LOG(LogTemp, Warning, TEXT("Threshold: %d"), Power_Threshold);
	}
}

void ADemoMan::RestartGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}
