// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PICKUP_API UPSaveGame : public USaveGame
{
	GENERATED_BODY()


public:
	UPSaveGame();

	// Player who scored
	UPROPERTY(VisibleAnywhere, Category = "Save stats")
		FString PlayerName;

	// Player's Score
	UPROPERTY(VisibleAnywhere, Category = "Save stats")
		float Score;

	// The save slot name
	UPROPERTY(VisibleAnywhere, Category = "Save stats")
		FString SaveSlotName;

	// The user index of save 
	UPROPERTY(VisibleAnywhere, Category = "Save stats")
		uint32 UserIndex;

	
};
