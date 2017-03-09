

#pragma once

#include "UObject/NoExportTypes.h"
#include "Model/JsonComponent.h"
#include "JsonModel.generated.h"

class ALootActor;
class UTankGameInstance;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UJsonModel : public UObject
{
	GENERATED_BODY()

public:
	void LoadFromFile(FString FileName);
	void PreLoad();
	void AttachToLootActor(ALootActor* Actor);

private:
	FString Parent = FString();
	TMap<FString, FString> Materials;
	TMap<FString, FString> Meshes;
	TMap<FString, UJsonComponent*> Components;

	UJsonModel* BuildCompositeModel(UTankGameInstance* GameInstance);
	UJsonModel* Clone();

public:
	static FORCEINLINE UStaticMesh* GetStaticMesh(FName Path)
	{
		return LoadObjFromPath<UStaticMesh>(Format(FString("Static Mesh'{0}'"), Path.ToString()));
	}

	static FORCEINLINE UMaterial* GetMaterial(FName Path)
	{
		return LoadObjFromPath<UMaterial>(Format(FString("Material'{0}'"), Path.ToString()));
	}


	template <typename ObjClass>
	static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;
		//~

		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
	}

	static FORCEINLINE FName Format(FString Format, FString ToAddToFormat)
	{
		FFormatOrderedArguments Args;
		Args.Add(FFormatArgumentValue(FText::FromString(ToAddToFormat)));

		auto FormattedText = FText::Format(FText::FromString(FString(Format)), Args);
		auto FormattedString = FormattedText.ToString();

		return FName(*FormattedString);
	}

};
