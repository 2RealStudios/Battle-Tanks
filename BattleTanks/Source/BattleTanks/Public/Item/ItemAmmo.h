

#pragma once

#include "Item/Item.h"
#include "ItemAmmo.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UItemAmmo : public UItem
{
	GENERATED_BODY()
	
public:

	int32 Amount = 1;

	virtual void OnLootActorSet(ALootActor* LootActor) override;
};
