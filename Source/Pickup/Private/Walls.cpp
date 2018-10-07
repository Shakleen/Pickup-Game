// Fill out your copyright notice in the Description page of Project Settings.

#include "Walls.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWalls::AWalls()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));			// Creating default object where we will place out static mesh component

	SineValue = 1.0;																	// Setting default values
	BaseColorRed = BaseColorGreen = BaseColorBlue = 0.0f;								// Setting default values
	LightColorBlue = LightColorGreen = LightColorRed = 0.0f;							// Setting default values
	Metal = Specular = Rough = 0.0f;													// Setting default values
}

// Called when the game starts or when spawned
void AWalls::BeginPlay()
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

}

