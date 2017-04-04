

#pragma once

#include "UObject/NoExportTypes.h"
#include "LootTableEntry.h"
#include "LootTable.generated.h"

/**
 * A weighted table used to determine what action is taken at a specified time i.e. enemy death->drop loot
 */
UCLASS()
class BATTLETANKS_API ULootTable : public UObject
{
	GENERATED_BODY()

public:
	// Load the table from the provided file
	bool loadFromFile(FString fileName);

	// Get a random loot from the table. Chance for a given entry is entry's weight/TotalWeight
	ULootTableEntry* GetLoot();

private:

	// The array of entries in the table 
	UPROPERTY()
	TArray<ULootTableEntry*> table;

	// The total weight of the table used to prevent constant recalculation of weight
	int32 TotalWeight = 0;
	
};


