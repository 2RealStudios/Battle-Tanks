

#pragma once

#include "Item/Item.h"
#include "ItemFuel.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UItemFuel : public UItem
{
	GENERATED_BODY()

public:
	int32 Amount = 1;
};
