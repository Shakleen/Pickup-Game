// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Spawner.h"
#include "../Public/BPickUp.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"

// Sets default values
ASpawner::ASpawner()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	MinRangeValue = -1000.f;
	MaxRangeValue = 1000.f;
	SpawnInterval = 0.5f;

	SineValue = 1.0;																	// Setting default values
	BaseColorRed = BaseColorGreen = BaseColorBlue = 0.0f;								// Setting default values
	LightColorBlue = LightColorGreen = LightColorRed = 0.0f;							// Setting default values
	Metal = Specular = Rough = 0.0f;													// Setting default values
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (MeshComp != NULL)
	{
		if (PickUpMaterial != NULL)
		{
			// Creating a dynamic material
			UMaterialInstanceDynamic * PickUpMaterialDynamic = UMaterialInstanceDynamic::Create(PickUpMaterial, this, NAME_None);

			// Setting Dynamic Material's Scalar Parameter values
			PickUpMaterialDynamic->SetScalarParameterValue(TEXT("Metal"), Metal);
			PickUpMaterialDynamic->SetScalarParameterValue(TEXT("Rough"), Rough);
			PickUpMaterialDynamic->SetScalarParameterValue(TEXT("Specular"), Specular);
			PickUpMaterialDynamic->SetScalarParameterValue(TEXT("WillEmit"), WillEmit);
			PickUpMaterialDynamic->SetScalarParameterValue(TEXT("IsSine"), SineValue);
			PickUpMaterialDynamic->SetScalarParameterValue(TEXT("IsCos"), 1.0f - SineValue);

			// Setting Dynamic Material's Vector Parameter values
			PickUpMaterialDynamic->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor(BaseColorRed, BaseColorGreen, BaseColorBlue));
			PickUpMaterialDynamic->SetVectorParameterValue(TEXT("LightColor"), FLinearColor(LightColorRed, LightColorGreen, LightColorBlue));

			// Setting the material on the mesh
			MeshComp->SetMaterial(0, PickUpMaterialDynamic);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Set material!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Set mesh!!"));
	}

	GetWorldTimerManager().SetTimer(SpawnHandle, this, &ASpawner::Spawn, SpawnInterval, true);
}

void ASpawner::Spawn()
{
	if (Battery != NULL && Bomb != NULL)
	{
		UWorld * World = GetWorld();

		if (World != NULL)
		{
			float X = FMath::RandRange(MinRangeValue, MaxRangeValue);
			float Y = FMath::RandRange(MinRangeValue, MaxRangeValue);
			FVector SpawnLocation = GetActorLocation() + FVector(X, Y, 0);

			int RandNo = FMath::RandRange(0.0f, 100.0f);

			FActorSpawnParameters SpawnParams = FActorSpawnParameters();

			if (RandNo >= 50.0f)
			{
				World->SpawnActor<ABPickUp>(Battery, SpawnLocation, GetActorRotation(), SpawnParams);
			}
			else
			{
				World->SpawnActor<ABPickUp>(Bomb, SpawnLocation, GetActorRotation(), SpawnParams);
			}
		}
	}
}

