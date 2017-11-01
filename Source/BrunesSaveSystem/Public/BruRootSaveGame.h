// Copyright Underflow Studios 2017

#pragma once

#include "CoreMinimal.h"
#include "BruSaveGame.h"
#include "BruRootSaveGame.generated.h"

/**
 * Holds all other save games.
 */
UCLASS()
class BRUNESSAVESYSTEM_API UBruRootSaveGame : public UBruSaveGame
{
	GENERATED_BODY()
	
	
public:
	
	UBruRootSaveGame();

	UPROPERTY(BlueprintReadOnly, Category = "Save System")
	TArray<FBruSaveInfo> SavedGames;
	
};
