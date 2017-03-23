

#pragma once

#include "Item/Item.h"
#include "ItemFuel.generated.h"

/**
 * The item that represents fuel
 */
UCLASS()
class BATTLETANKS_API UItemFuel : public UItem
{
	GENERATED_BODY()

public:
	// The amount of fuel to be added to the tank
	int32 Amount = 1;
};
