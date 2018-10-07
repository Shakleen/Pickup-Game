// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupGameModeBase.h"
#include "PGameMode.generated.h"


class APCharacter;
class UPSaveGame;

/**
 * 
 */
UCLASS()
class PICKUP_API APGameMode : public APickupGameModeBase
{
	GENERATED_BODY()
	
private:
	void SetHighScore(const FString & Name, float Score);


protected:
	
	// Save game
	UFUNCTION(BlueprintCallable)
		void SaveGame(const FString & Name, float Score);

	// Load saved game
	UFUNCTION(BlueprintCallable)
		void LoadGame();

	// Name of highest scorer
	UPROPERTY(BlueprintReadOnly, Category = "Player Score")
		FString HighScoreName;

	// Highest score
	UPROPERTY(BlueprintReadOnly, Category = "Player Score")
		float HighScore;

};
