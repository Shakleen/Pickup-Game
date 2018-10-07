// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/PCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Engine/Public/TimerManager.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APCharacter::APCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanJump = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp);

	// How frequently health will be deducted
	Interval = 0.1f;

	// Value of initial and max health
	Health = MaxHealth = 10.0f;
	Ratio = 1.0f;

	// The player isn't initially dead
	IsDead = false;
}

// Called when the game starts or when spawned
void APCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &APCharacter::TickFunction, Interval, true);
}


void APCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}


void APCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * Value);
}


void APCharacter::JumpUp()
{
	Jump();
}


void APCharacter::TickFunction()
{
	Age += Interval;

	Damage(Interval);
}


void APCharacter::Damage(float Value)
{
	Health -= Value;

	Ratio = Health / MaxHealth;

	if (Health <= 0.0f)
	{
		IsDead = true;

		GetWorldTimerManager().ClearTimer(DamageTimerHandle);

		DetachFromControllerPendingDestroy();

		OnDeathEvent();
	}
}


void APCharacter::Heal(float Value)
{
	Health += Value;

	if (Health > MaxHealth)
	{
		Health = MaxHealth;
	}

	Ratio = Health / MaxHealth;
}


// Called every frame
void APCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Camera movement
	PlayerInputComponent->BindAxis("LookUp", this, &APCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &APCharacter::AddControllerYawInput);

	// Character Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &APCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APCharacter::MoveRight);

	// Jump mechanics
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APCharacter::JumpUp);
	
	// Pauses Game
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APCharacter::PauseGame);
}

