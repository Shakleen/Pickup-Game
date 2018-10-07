// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class PICKUP_API ADoor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent * DoorFrame;

	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent * Door;

	UPROPERTY(EditAnywhere, Category = "Components")
		UBoxComponent * Box;
	UFUNCTION()
	void OverlappedDoor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
