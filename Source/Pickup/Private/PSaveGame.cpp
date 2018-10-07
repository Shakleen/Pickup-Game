// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/PSaveGame.h"

#define SAVE_GAME_SLOT TEXT("Save")
#define SAVE_GAME_USER_INDEX 0

// Constructor
UPSaveGame::UPSaveGame()
{
	SaveSlotName = SAVE_GAME_SLOT;
	UserIndex = SAVE_GAME_USER_INDEX;
}

