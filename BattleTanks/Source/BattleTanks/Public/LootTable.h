

#pragma once

#include "UObject/NoExportTypes.h"
#include "LootTableEntry.h"
#include "LootTable.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ULootTable : public UObject
{
	GENERATED_BODY()

public:
	ULootTable();
	bool loadFromFile(FString fileName);

	ULootTableEntry* GetLoot();

private:
	TArray<ULootTableEntry*> table;
	int32 TotalWeight = 0;
	
};

//	FString idk;
//	uint32 weight;


