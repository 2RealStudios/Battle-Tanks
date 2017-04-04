

#pragma once

#include "UObject/NoExportTypes.h"
#include "Tank.h"
#include "Item.generated.h"

/**
 * The base item class that all items must extends inorder to properly be used
 */
UCLASS()
class BATTLETANKS_API UItem : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnCollide(ATank* Actor);
};

