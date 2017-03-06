

#pragma once

#include "UObject/NoExportTypes.h"
#include "LootTableEntry.h"
#include "LootTable.generated.h"

/**
 * In a loot table using the following formats in the name of the entry will cause different outcomes
 *		"loot:XXXXX": roll again but under the loot table named XXXXX
 */
UCLASS()
class BATTLETANKS_API ULootTable : public UObject
{
	GENERATED_BODY()

public:
	bool loadFromFile(FString fileName);

	ULootTableEntry* GetLoot();

private:
	TArray<ULootTableEntry*> table;

	int32 TotalWeight = 0;
	
};


