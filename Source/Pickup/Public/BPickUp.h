// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPickUp.generated.h"

// Forward Declaration
class UStaticMeshComponent;
class UBoxComponent;
class UParticleSystem;
class APCharacter;
class UPrimitiveComponent;
class USoundBase;
class UMaterialInterface;
class URadialForceComponent;

UCLASS()
class PICKUP_API ABPickUp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABPickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The mesh we want the pick up to have will be stored here
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent * MeshComp;

	// This will handle ouir overlap events
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent * BoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent * RadialForceComp;

	// How long the pickup will last
	UPROPERTY(EditDefaultsOnly, Category = "Pickup Stats")
		float LifeSpan;

	// TImerHandle for pick up 
	FTimerHandle LifeTimerHandle;

	// Particle to play when the pickup is interacted with the player
	UPROPERTY(EditDefaultsOnly, Category = "FX")
		UParticleSystem * InteractFX;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
		USoundBase * InteractSound;

	UFUNCTION()
		void PickupBehaviour(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	// The logic to heal players
	UPROPERTY(EditDefaultsOnly, Category = "Pickup Stats")
		float HealAmount;

	// The logic to damage players
	UPROPERTY(EditDefaultsOnly, Category = "Pickup Stats")
		float DamageAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Pickup Stats")
		bool bPickUpType;

	// The material we want to edit before applying
	UPROPERTY(EditDefaultsOnly, Category = "Materials")
		UMaterialInterface * PickUpMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Materials", meta = (EditCondition = "bPickUpType"))
		float SineValue;

	UPROPERTY(EditDefaultsOnly, Category = "Materials", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
		float BaseColorRed;

	UPROPERTY(EditDefaultsOnly, Category = "Materials", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
		float BaseColorGreen;

	UPROPERTY(EditDefaultsOnly, Category = "Materials", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
		float BaseColorBlue;

	UPROPERTY(EditDefaultsOnly, Category = "Materials", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
		float LightColorRed;

	UPROPERTY(EditDefaultsOnly, Category = "Materials", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
		float LightColorGreen;

	UPROPERTY(EditDefaultsOnly, Category = "Materials", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
		float LightColorBlue;

	UPROPERTY(EditDefaultsOnly, Category = "Materials", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
		float Metal;

	UPROPERTY(EditDefaultsOnly, Category = "Materials", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
		float Rough;

	UPROPERTY(EditDefaultsOnly, Category = "Materials", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
		float Specular;

	UPROPERTY(EditDefaultsOnly, Category = "Materials", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
		float WillEmit;

	void TickFunction();

public:



};
