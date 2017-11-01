// Copyright Underflow Studios 2017

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BruSaveSystemTypes.h"
#include "BruSaveGame.generated.h"

/**
 *
 */
UCLASS()
class BRUNESSAVESYSTEM_API UBruSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UBruSaveGame();

	//Basic save information such as save slot name and which user.
	UPROPERTY(BlueprintReadWrite, Category = "Save System")
	FBruSaveInfo SaveInfo;

	UPROPERTY(BlueprintReadWrite, Category = "Location")
	FTransform SavedPlayerTransform;

	UPROPERTY(BlueprintReadWrite, Category = "Mission System Saves")
	TArray<FBruMissionSaveInfo> MissionSaveInfos;

	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FBruMovementSaveInfo SavedPlayerMovement;
};
