

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
	
	template <typename ObjClass>
	static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;
		//~

		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
	}


public:
	virtual void OnLootActorSet(ALootActor* LootActor);
	

	
};

