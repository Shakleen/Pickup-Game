// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/BPickUp.h"
#include "../Public/PCharacter.h"
#include "Engine/Public/TimerManager.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "PhysicsEngine/RadialForceComponent.h"


// Sets default values
ABPickUp::ABPickUp()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Comp"));			// Creating default object where we will place out static mesh component
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);					// Setting the mesh to have no collision with anything
	MeshComp->SetCollisionObjectType(ECC_PhysicsBody);									// Setting collision object type
	MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);						// Setting the mesh to ignore everything. Because we'll handle this with Box Component.
	MeshComp->SetSimulatePhysics(true);													// The mesh will be simulating physics

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));					// Creating default subobject
	BoxComp->SetBoxExtent(FVector(50, 50, 50));											// Setting up the box size
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);							// Setting the box to have no collision with anything
	BoxComp->SetCollisionResponseToAllChannels(ECR_Ignore);								// Setting the box to ignore everything.
	BoxComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);						// Setting the box to only query overlaps with pawn class.
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABPickUp::PickupBehaviour);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force Comp"));
	RadialForceComp->Radius = 300.0f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->bIgnoreOwningActor = true;
	RadialForceComp->bAutoActivate = false;

	RootComponent = MeshComp;															// Making Box component the root component
	BoxComp->SetupAttachment(MeshComp);													// Attaching to box compoonent
	RadialForceComp->SetupAttachment(RootComponent);

	LifeSpan = 5.0f;																	// Setting initial life span
	HealAmount = DamageAmount = 1.0f;													// Setting initial Heal and Damage Amounts
	bPickUpType = false;																// True -> Battery, False -> Bomb

	SineValue = 1.0;																	// Setting default values
	BaseColorRed = BaseColorGreen = BaseColorBlue = 0.0f;								// Setting default values
	LightColorBlue = LightColorGreen = LightColorRed = 0.0f;							// Setting default values
	Metal = Specular = Rough = 0.0f;													// Setting default values
}

// Called when the game starts or when spawned
void ABPickUp::BeginPlay()
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

	// Setting up timer function to call death
	GetWorldTimerManager().SetTimer(LifeTimerHandle, this, &ABPickUp::TickFunction, LifeSpan, true);
}


void ABPickUp::PickupBehaviour(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// Casting to our player class
	APCharacter * Player = Cast<APCharacter>(OtherActor);

	// If the cast succeeds meaning that if the overlapped actor is out player then perform the following logic
	if (Player != NULL)
	{
		if (Player->IsDead == false)
		{
			if (bPickUpType == true)
			{
				Player->Heal(HealAmount);
			}
			else
			{
				Player->Damage(DamageAmount);
				RadialForceComp->FireImpulse();
			}

			if (InteractFX != NULL)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), InteractFX, GetActorLocation(), GetActorRotation());
			}

			if (InteractSound != NULL)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), InteractSound, GetActorLocation());
			}

			Destroy();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT PLAYER!"))
	}
}


void ABPickUp::TickFunction()
{
	Destroy();
}


