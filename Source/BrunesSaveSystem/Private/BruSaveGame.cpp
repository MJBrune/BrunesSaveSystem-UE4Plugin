// Copyright Underflow Studios 2017

#include "BruSaveGame.h"




UBruSaveGame::UBruSaveGame()
{
	SaveInfo.SaveSlotName = TEXT("SneakerNet");
	SaveInfo.UserIndex = 0;
	SaveInfo.SaveTime = FDateTime::Now();
}
