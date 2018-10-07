// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Walls.generated.h"

UCLASS()
class PICKUP_API AWalls : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWalls();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The mesh we want the pick up to have will be stored here
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent * MeshComp;

	// The material we want to edit before applying
	UPROPERTY(EditDefaultsOnly, Category = "Materials")
		UMaterialInterface * PickUpMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Materials", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
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

public:	

	
	
};
