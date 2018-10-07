// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PCharacter.generated.h"

// Forward Declaration
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PICKUP_API APCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APCharacter();

	// Function that causes damage
	void Damage(float Value);

	// Function that heals
	void Heal(float Value);

	UPROPERTY(BlueprintReadOnly, Category = "Player Stats")
		bool IsDead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Movement logic
	void MoveForward(float Value);
	void MoveRight(float Value);

	// Jump logic
	void JumpUp();

	// Health variables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
		float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
		float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
		float Ratio;

	// Survival time
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
		float Age;

	// Called every "Interval" amount of time
	void TickFunction();


	FTimerHandle DamageTimerHandle;

	float Interval;

	// Function to be implemented in blueprint , Pauses game
	UFUNCTION(BlueprintImplementableEvent, Category = "Player Functions")
		void PauseGame();

	// 3RD Person Camera
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UCameraComponent * CameraComp;

	// Binding Camera to controller
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		USpringArmComponent * SpringArmComp;

	UFUNCTION(BlueprintImplementableEvent, Category = "Player Functions")
		void OnDeathEvent();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
