

#pragma once

#include "Item/Item.h"
#include "ItemAmmo.generated.h"

/**
 * The item that represents ammo
 */
UCLASS()
class BATTLETANKS_API UItemAmmo : public UItem
{
	GENERATED_BODY()
	
public:
	// The amount of ammo to be added to the tank
	int32 Amount = 1;
	void OnCollide(ATank* Actor) override;

};
