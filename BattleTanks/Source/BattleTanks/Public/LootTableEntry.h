

#pragma once

#include "UObject/NoExportTypes.h"
#include "LootTableEntry.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ULootTableEntry : public UObject
{
	GENERATED_BODY()

public:
	// Default Constuctor
	ULootTableEntry();

	UPROPERTY()
	// The action/loot table the is associated with this entry
	FString name;

	UPROPERTY()
	// The weight of this entry. How often it gets picked
	int32 weight;
	
	
};
