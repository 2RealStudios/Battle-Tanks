

#pragma once

#include "UObject/NoExportTypes.h"
#include "Model/JsonComponent.h"
#include "JsonModel.generated.h"

class UTankGameInstance;

/**
 * Holds the data to physically represent an item in game
 */
UCLASS()
class BATTLETANKS_API UJsonModel : public UObject
{
	GENERATED_BODY()

public:
	// This models name
	UPROPERTY()
	FString Name = FString();

	// Load this model from the file provided
	void LoadFromFile(FString FileName);

	// Find all assets for the Model Manager to preload puts meshes in one set and material in the other
	void PreloadAssets(TSet<FString> &MeshesToLoad, TSet<FString> &MaterialToLoad);

	// Attach this model to the LootActor provided
	TMap<FString, USceneComponent*> AttachToActor(AActor* Actor);



private:

	// This models parent model
	UPROPERTY()
	FString Parent = FString();

	// Holds unquie identifiers of material paths, useful for extending a model via the parent model
	UPROPERTY()
	TMap<FString, FString> Materials;

	// Holds unquie identifiers of mesh paths, useful for extending a model via the parent model
	UPROPERTY()
	TMap<FString, FString> Meshes;

	// Holds the references to the components this model will have
	UPROPERTY()
	TMap<FString, UJsonComponent*> Components;

	// Builds a Model based on the parent model of this model
	UJsonModel* BuildCompositeModel(UTankGameInstance* GameInstance);

	// Builds a compsite component that takes in to account all the parenting during creation
	UJsonComponent* BuildCompsiteComponent(UJsonModel* Model, UJsonComponent* JsonComponent);

	// Builds a compsite component that takes in to account all the parenting during creation
	UJsonComponent* BuildCompsiteComponent(UJsonComponent* Parent, UJsonComponent* JsonComponent);

	// Clones this model and return a new instance
	UJsonModel* Clone();

public:

	// 
	static FORCEINLINE UStaticMesh* GetStaticMesh(FName Path)
	{
		return LoadObjFromPath<UStaticMesh>(Format(FString("Static Mesh'{0}'"), Path.ToString()));
	}


	static FORCEINLINE UMaterial* GetMaterial(FName Path)
	{
		return LoadObjFromPath<UMaterial>(Format(FString("Material'{0}'"), Path.ToString()));
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
