// Copyright Underflow Studios 2017

#include "BruSaveGameManager.h"
#include "BruRootSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformFile.h"

UBruSaveGameManager::UBruSaveGameManager()
{

}

void UBruSaveGameManager::Init()
{
	RootSave = Cast<UBruRootSaveGame>(UGameplayStatics::CreateSaveGameObject(UBruRootSaveGame::StaticClass()));
	UBruRootSaveGame* LoadedSaveGame = Cast<UBruRootSaveGame>(UGameplayStatics::LoadGameFromSlot(RootSave->SaveInfo.SaveSlotName, RootSave->SaveInfo.UserIndex));

	if (IsValid(LoadedSaveGame))
	{
		RootSave = LoadedSaveGame;
	}
}

void UBruSaveGameManager::GetSavedGames(TArray<FBruSaveInfo>& OutSavedGames)
{
	check(RootSave); // How did you call this before Init was called in order to set the RootSave?

	OutSavedGames = RootSave->SavedGames;
}

bool UBruSaveGameManager::SaveGame(FString SaveGameName, FString& FailReason)
{
	if (SaveGameName == RootSave->SaveInfo.SaveSlotName)
	{
		return false; //I told you not to use the root save slot name. Don't overwrite the rootsave slot.
	}

	UBruSaveGame* TempSaveGame = Cast<UBruSaveGame>(UGameplayStatics::CreateSaveGameObject(UBruSaveGame::StaticClass()));
	FBruSaveInfo SaveGameInfo;
	SaveGameInfo.FriendlySaveSlotName = SaveGameName;
	SaveGameInfo.SavedMapName = UGameplayStatics::GetCurrentLevelName(GetWorldFromContext(), true);
	SaveGameInfo.SaveTime = FDateTime::Now();
	SaveGameInfo.SaveSlotName = SaveGameName + FDateTime::Now().ToString();

	RootSave->SavedGames.Add(SaveGameInfo);
	TempSaveGame->SaveInfo = SaveGameInfo;

	if (FillSaveData(TempSaveGame, FailReason))
	{
		if (UGameplayStatics::SaveGameToSlot(TempSaveGame, SaveGameInfo.SaveSlotName, SaveGameInfo.UserIndex))
		{
			UGameplayStatics::SaveGameToSlot(RootSave, RootSave->SaveInfo.SaveSlotName, RootSave->SaveInfo.UserIndex);
			return true;
		}
		return false;
	}

	return false;
}

bool UBruSaveGameManager::LoadGame(FBruSaveInfo SavedGameInfo, FString& FailReason)
{
	if (SavedGameInfo.SaveSlotName == RootSave->SaveInfo.SaveSlotName)
	{
		FailReason = "AJPSaveGameManager::LoadGame - SavedGameInfo was the same as roots: " + RootSave->SaveInfo.SaveSlotName;
		return false; //I told you not to use the root save slot name. Don't try to manually load the root save
	}

	UBruSaveGame* LoadedSaveGame = Cast<UBruSaveGame>(UGameplayStatics::LoadGameFromSlot(SavedGameInfo.SaveSlotName, SavedGameInfo.UserIndex));

	if (IsValid(LoadedSaveGame))
	{
		UGameplayStatics::OpenLevel(GetWorldFromContext(), *LoadedSaveGame->SaveInfo.SavedMapName);
		CachedSaveGame = LoadedSaveGame;
		return true;
	}

	FailReason = "AJPSaveGameManager::LoadGame - LoadedSaveGame was not valid";

	return false;
}

void UBruSaveGameManager::GetAllSaveGames(TArray<FString>& OutSaves)
{
	OutSaves.Empty();

	FString SavePath = FString::Printf(TEXT("%sSaveGames"), *FPaths::ProjectSavedDir());
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	class MyDirectoryVisitor : public IPlatformFile::FDirectoryVisitor
	{
	public:
		TArray<FString> Saves;
		virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
		{
			if (FPaths::GetExtension(FilenameOrDirectory, false) == TEXT("sav"))
			{
				FString SaveName = FPaths::GetBaseFilename(FilenameOrDirectory);
				Saves.Add(SaveName);
			}
			return true;
		}
	} DirectoryVisitor;

	PlatformFile.IterateDirectory(*SavePath, DirectoryVisitor);

	OutSaves.Append(DirectoryVisitor.Saves);
}

bool UBruSaveGameManager::DeleteSaveGame(FBruSaveInfo SavedGameInfo)
{
	if (SavedGameInfo.SaveSlotName == RootSave->SaveInfo.SaveSlotName)
	{
		UGameplayStatics::DeleteGameInSlot(RootSave->SaveInfo.SaveSlotName, RootSave->SaveInfo.UserIndex);
		RootSave = Cast<UBruRootSaveGame>(UGameplayStatics::CreateSaveGameObject(UBruRootSaveGame::StaticClass()));
		UGameplayStatics::SaveGameToSlot(RootSave, RootSave->SaveInfo.SaveSlotName, RootSave->SaveInfo.UserIndex);
		return true;
	}

	RootSave->SavedGames.RemoveAll([&](const FBruSaveInfo Ptr) {
		return SavedGameInfo.SaveSlotName == Ptr.SaveSlotName;
	});

	return UGameplayStatics::DeleteGameInSlot(SavedGameInfo.SaveSlotName, SavedGameInfo.UserIndex);
}

bool UBruSaveGameManager::FillSaveData(UBruSaveGame* NewSaveGame, FString& FailReason)
{
	if (!IsValid(NewSaveGame))
	{
		FailReason = "AJPSaveGameManager::FillSaveData - NewSaveGame was not valid";
		return false; //If this isn't valid then what are we doing?
	}

	APlayerController* JPPlayerController = Cast<APlayerController>(GetWorldFromContext()->GetFirstPlayerController());

	if (!IsValid(JPPlayerController))
	{
		return false;
	}

	NewSaveGame->SavedPlayerTransform = JPPlayerController->GetPawn()->GetActorTransform();

	return true;

}

bool UBruSaveGameManager::LoadDataFromSave(UBruSaveGame* LoadedGameSave, FString& FailReason)
{
	if (!IsValid(LoadedGameSave))
	{
		FailReason = "AJPSaveGameManager::LoadDataFromSave - LoadedGameSave was not valid";
		return false; //If this isn't valid then what are we doing?
	}

	APlayerController* JPPlayerController = Cast<APlayerController>(GetWorldFromContext()->GetFirstPlayerController());

	if (!IsValid(JPPlayerController))
	{
		return false;
	}

	SavedPlayerStart = GetWorldFromContext()->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), LoadedGameSave->SavedPlayerTransform);

	return true;
}
