

#pragma once

#include "UObject/NoExportTypes.h"
#include "SoundManager.generated.h"

class UTankGameInstance;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API USoundManager : public UObject
{
	GENERATED_BODY()
	
public:

	void Init(UTankGameInstance* GameInstance);

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlaySound(FString SoundName, const UObject* WorldContextObject, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundConcurrency* ConcurrencySettings = nullptr);

	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlaySoundAt(FString SoundName, const UObject* WorldContextObject, FVector Location, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = nullptr, class USoundConcurrency* ConcurrencySettings = nullptr);
	
	UFUNCTION(BlueprintCallable, Category = "Sound")
	void PlaySoundAtR(FString SoundName, const UObject* WorldContextObject, FVector Location, FRotator Rotation, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = nullptr, class USoundConcurrency* ConcurrencySettings = nullptr);

private:
	// The map holding all references to the items
	UPROPERTY()
	TMap<FString, USoundBase*> Sounds;
	
	TMap<FString, USoundBase*> LoadSounds();

	USoundBase* GetSound(FString SoundName);







public:

	// 
	static FORCEINLINE USoundCue* GetSoundCue(FName Path)
	{
		return LoadObjFromPath<USoundCue>(Format(FString("SoundCue'{0}'"), Path.ToString()));
	}


	static FORCEINLINE USoundWave* GetSoundWave(FName Path)
	{
		return LoadObjFromPath<USoundWave>(Format(FString("SoundWave'{0}'"), Path.ToString()));
	}

	// Get an object and load it, to be honest not sure how it works....
	template <typename ObjClass>
	static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;
		//~

		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
	}

	/*
	Takes a string (Format) that can be formated with one argument (ToAddToFormat)
	Mostly here to prevent duplicate code
	example: Format = "Hello {0}", ToAddToFormat = "World", Output = "Hello World"
	*/
	static FORCEINLINE FName Format(FString Format, FString ToAddToFormat)
	{
		FFormatOrderedArguments Args;
		Args.Add(FFormatArgumentValue(FText::FromString(ToAddToFormat)));

		auto FormattedText = FText::Format(FText::FromString(FString(Format)), Args);
		auto FormattedString = FormattedText.ToString();

		return FName(*FormattedString);
	}
};

