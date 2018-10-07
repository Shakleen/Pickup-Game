// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class ABPickUp;
class UStaticMeshComponent;
class UMaterialInterface;

UCLASS()
class PICKUP_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
		UStaticMeshComponent * MeshComp;

	// What class to spawn
	UPROPERTY(EditDefaultsOnly, Category = "Spawner Stats")
		TSubclassOf <ABPickUp> Battery;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner Stats")
		TSubclassOf <ABPickUp> Bomb;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner Stats")
		float MaxRangeValue;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner Stats")
		float MinRangeValue;

	UPROPERTY(EditDefaultsOnly, Category = "Spawner Stats")
		float SpawnInterval;

	FTimerHandle SpawnHandle;

	UFUNCTION()
		void Spawn();

	FActorSpawnParameters SpawnParams;

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
	
};
