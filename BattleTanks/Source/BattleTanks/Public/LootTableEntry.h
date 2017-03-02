

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
	ULootTableEntry();
	~ULootTableEntry();

	UPROPERTY()
	FString name;

	UPROPERTY()
	int32 weight;
	
	
};
