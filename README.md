# BrunesSaveSystem-UE4Plugin
A simple and open source save system for UE4. Geared towards large single player RPGs.


### Usage ###

BruSaveGameManager is a class you should create a child of. This will allow you to override the methods that fill saves and load data from saves so that you can include your own save data.

Additionally you should create your own GameInstance and initialize the save system during Init(). Should look something like this:
```
class JUMPER_API UJPGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;

	bool bSavedGameWasLoaded = false;

	UFUNCTION(BlueprintCallable, Category = "Saved Games")
	UBruSaveGameManager* GetSavedGameManager();

private:

	UPROPERTY()
	UBruSaveGameManager* SavedGameManagerInstance;
	
};
```

```
void UJPGameInstance::Init()
{
	GetSavedGameManager();
}

UBruSaveGameManager* UJPGameInstance::GetSavedGameManager()
{
	if (!IsValid(SavedGameManagerInstance))
	{
		SavedGameManagerInstance = NewObject<UBruSaveGameManager>(GetTransientPackage(), UBruSaveGameManager::StaticClass());
		SavedGameManagerInstance->WorldContext = GetWorldContext();
		SavedGameManagerInstance->Init();
	}

	return SavedGameManagerInstance;
}
```

### Commit Guide

Follow https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/ and https://github.com/Allar/ue4-style-guide

### License

BSD 2-Clause License

Copyright (c) 2017, Michael Brune
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
