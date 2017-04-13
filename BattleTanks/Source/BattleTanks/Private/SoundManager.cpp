

#include "BattleTanks.h"
#include "TankGameInstance.h"
#include "SoundManager.h"




void USoundManager::Init(UTankGameInstance* GameInstance)
{
	Sounds = LoadSounds();
}


void USoundManager::PlaySound(FString SoundName, const UObject * WorldContextObject, float VolumeMultiplier, float PitchMultiplier, float StartTime, USoundConcurrency * ConcurrencySettings)
{
	USoundBase* Sound = GetSound(SoundName);
	if (!Sound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sound with name: %s not found"), *SoundName)
		return;
	}

	UGameplayStatics::PlaySound2D(WorldContextObject, Sound, VolumeMultiplier, PitchMultiplier, StartTime, ConcurrencySettings);

}

void USoundManager::PlaySoundAt(FString SoundName, const UObject* WorldContextObject, FVector Location, float VolumeMultiplier , float PitchMultiplier , float StartTime, class USoundAttenuation* AttenuationSettings , class USoundConcurrency* ConcurrencySettings)
{
	USoundBase* Sound = GetSound(SoundName);
	if (!Sound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sound with name: %s not found"), *SoundName)
			return;
	}
	UGameplayStatics::PlaySoundAtLocation(WorldContextObject, Sound, Location, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings);
}

void USoundManager::PlaySoundAt(FString SoundName, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier, float PitchMultiplier, float StartTime, class USoundAttenuation* AttenuationSettings, class USoundConcurrency* ConcurrencySettings)
{
	USoundBase* Sound = GetSound(SoundName);
	if (!Sound) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Sound with name: %s not found"), *SoundName)
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(WorldContextObject, Sound, Location, Rotation, VolumeMultiplier, PitchMultiplier, StartTime, AttenuationSettings, ConcurrencySettings);
}

USoundBase* USoundManager::GetSound(FString SoundName)
{
	if (!Sounds.Contains(SoundName))
	{
		return nullptr;
	}
	return Sounds[SoundName];
}


TMap<FString, USoundBase*> USoundManager::LoadSounds()
{
	TMap<FString, USoundBase*> mSounds; // Holds all models created

	UE_LOG(LogTemp, Warning, TEXT("Loading Sounds"))

	IFileManager& FileManager = IFileManager::Get();  // Get file manager to read files

	TArray<FString> files; // Files in the /Content/Model/ directory

	FString gameDir = FPaths::GameContentDir() + "Sounds/"; // Directory to check
	FileManager.FindFiles(files, *gameDir); // Find all files that match
	for (auto& FileName : files)
	{
		auto SoundName = FPaths::GetBaseFilename(FileName);

		auto AssetLocation = "/Game/Sounds/" + SoundName + "." + SoundName;
		UE_LOG(LogTemp, Warning, TEXT("Loading %s"), *SoundName)

		USoundBase* sound = GetSoundCue(FName(*AssetLocation)); // Create model
		
		if (!sound)
			sound = GetSoundWave(FName(*AssetLocation));

		if (sound) 
		{
			UE_LOG(LogTemp, Warning, TEXT("Loaded %s"), *FileName)
			mSounds.Add(SoundName, sound); // Add model to map
		}
	}

	// Return the map of models
	return mSounds;
}

