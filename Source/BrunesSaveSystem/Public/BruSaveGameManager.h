// Copyright Underflow Studios 2017

#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "UObject/NoExportTypes.h"
#include "BruRootSaveGame.h"
#include "BruSaveGameManager.generated.h"

UCLASS()
class BRUNESSAVESYSTEM_API UBruSaveGameManager : public UObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UBruSaveGameManager();

	virtual void Init();

	FWorldContext* WorldContext;

	virtual UWorld* GetWorldFromContext() { return WorldContext ? WorldContext->World() : NULL; }
public:

	//returns (via reference) an array of saved game information.
	UFUNCTION(BlueprintCallable, Category = "Save System")
	virtual void GetSavedGames(TArray<FBruSaveInfo>& OutSavedGames);

	//Saves a game as long as it doesn't match the root save slot name.
	//returns true if it successfully saved the game.
	UFUNCTION(BlueprintCallable, Category = "Save System")
	virtual bool SaveGame(FString SaveGameName, FString& FailReason);

	//Loads a game from save info as long as it doesn't match the root save name.
	//returns true if it successfully loaded the save game data.
	UFUNCTION(BlueprintCallable, Category = "Save System")
	virtual bool LoadGame(FBruSaveInfo SavedGameInfo, FString& FailReason);
	
	//Gets all of the save game files in the current saved game directory.
	//returns all saved games through the outsaves array reference.
	UFUNCTION(BlueprintCallable, Category = "Save System")
	virtual void GetAllSaveGames(TArray<FString>& OutSaves);

	//Deletes a saved game EVEN IF it matches the root save name. (Will recreate root save)
	//return true if it successfully deleted the save game.
	UFUNCTION(BlueprintCallable, Category = "Save System")
	virtual bool DeleteSaveGame(FBruSaveInfo SavedGameInfo);

	//Fills a new save file with save data.
	//returns true if it successfully filled the save with data
	UFUNCTION(BlueprintCallable, Category = "Save System")
	virtual bool FillSaveData(UBruSaveGame* NewSaveGame, FString& FailReason);

	//loads a save game from data. Called during ReadyToStartMatch
	//returns true if it successfully loaded, false means bad FJPSaveInfo data.
	UFUNCTION(BlueprintCallable, Category = "Save System")
	virtual bool LoadDataFromSave(UBruSaveGame* LoadedGameSave, FString& FailReason);

	UPROPERTY(BlueprintReadOnly, Category = "Save System")
	UBruSaveGame* CachedSaveGame;

	UPROPERTY(BlueprintReadOnly, Category = "Save System")
	AActor* SavedPlayerStart;

private:
	//This save holds information on all the other saves.
	UPROPERTY()
	UBruRootSaveGame* RootSave;
	
};
