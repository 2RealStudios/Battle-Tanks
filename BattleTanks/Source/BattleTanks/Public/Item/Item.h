

#pragma once

#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

class ALootActor;


/**
 * 
 */
UCLASS()
class BATTLETANKS_API UItem : public UObject
{
	GENERATED_BODY()

public:
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

	virtual void OnLootActorSet(ALootActor* LootActor);
	//virtual void OnCollide(AActor* Actor)?

protected:
	UStaticMesh* GetStaticMesh(FName Path);
	UMaterial* GetMaterial(FName Path);

};

