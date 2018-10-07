// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/PGameMode.h"
#include "../Public/PSaveGame.h"
#include "Kismet/GameplayStatics.h"


#define SAVE_GAME_SLOT TEXT("Save")
#define SAVE_GAME_USER_INDEX 0


void APGameMode::SaveGame(const FString & Name, float Score)
{
	UPSaveGame * SavedGame = NULL;

	// Check if save game exists. If it does then just update save game, otherwise create a new one.
	if (UGameplayStatics::DoesSaveGameExist(SAVE_GAME_SLOT, SAVE_GAME_USER_INDEX))
	{
		SavedGame = Cast<UPSaveGame>(UGameplayStatics::LoadGameFromSlot(SAVE_GAME_SLOT, SAVE_GAME_USER_INDEX));

		if (SavedGame != NULL)
		{
			// Update only if high score is beaten.
			if (SavedGame->Score < Score)
			{
				SavedGame->Score = Score;
				SavedGame->PlayerName = Name;
			}
		}
	}
	
	if (SavedGame == NULL)
	{
		SavedGame = Cast<UPSaveGame>(UGameplayStatics::CreateSaveGameObject(UPSaveGame::StaticClass()));

		SavedGame->PlayerName = Name;
		SavedGame->Score = Score;
	}

	SetHighScore(SavedGame->PlayerName, SavedGame->Score);
	UGameplayStatics::SaveGameToSlot(SavedGame, SavedGame->SaveSlotName, SavedGame->UserIndex);
}


void APGameMode::LoadGame()
{
	// Check if save game exists first
	if (UGameplayStatics::DoesSaveGameExist(SAVE_GAME_SLOT, SAVE_GAME_USER_INDEX))
	{
		UPSaveGame * SavedGame = Cast<UPSaveGame>(UGameplayStatics::LoadGameFromSlot(SAVE_GAME_SLOT, SAVE_GAME_USER_INDEX));

		// Check if SavedGame is valid
		if (SavedGame != NULL)
		{
			SetHighScore(SavedGame->PlayerName, SavedGame->Score);
		}
		else
		{
			SetHighScore("N/A", 0);
		}
	}
}


void APGameMode::SetHighScore(const FString & Name, float Score)
{
	// Update player name for viewing
	HighScoreName = Name;

	// Update the high score for viewing
	HighScore = Score;
}
