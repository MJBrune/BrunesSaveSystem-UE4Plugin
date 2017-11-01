// Copyright Underflow Studios 2017

#pragma once
#include "BruSaveSystemTypes.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FBruSaveInfo
{
	GENERATED_USTRUCT_BODY()

public:
	
	bool operator==(const FBruSaveInfo& OtherInfo) const
	{
		return OtherInfo.SaveSlotName == SaveSlotName;
	}

	//The Friendly name for this save slot.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	FString FriendlySaveSlotName = TEXT("SneakerNet");

	//Save Slot Name for the machines
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	FString SaveSlotName = TEXT("RootSaveSlot");

	//The current save's map name.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	FString SavedMapName;

	//The user number for the save slot... dunno why?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	int32 UserIndex = 0;

	//The DateTime of When the game  was saved.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	FDateTime SaveTime;
};

USTRUCT(BlueprintType, Blueprintable)
struct FBruMissionTaskSaveInfo
{
	GENERATED_USTRUCT_BODY()

public:

	//The unique mission task name to find the mission task class.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	FString SavedMissionTaskClassString;

	//If the mission task is completed or not.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	bool bIsCompleted;
};

USTRUCT(BlueprintType, Blueprintable)
struct FBruMissionSaveInfo
{
	GENERATED_USTRUCT_BODY()

public:

	//The unique mission name to find the mission class.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	FString SavedMissionClassString;

	//If the mission is completed or not.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	bool bIsCompleted;

	//If the mission is completed or not.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	TArray<FBruMissionTaskSaveInfo> TaskSaveInfos;
};

USTRUCT(BlueprintType, Blueprintable)
struct FBruMovementSaveInfo
{
	GENERATED_USTRUCT_BODY()

public:

	//The velocity of the player at the point of saving
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	FVector SaveVelocity;

	//If the player is crouched or not on load
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Basic)
	bool bIsCrouched;
};