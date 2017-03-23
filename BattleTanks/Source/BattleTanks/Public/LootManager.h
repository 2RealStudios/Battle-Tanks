

#pragma once

#include "UObject/NoExportTypes.h"
#include "LootManager.generated.h"

class ULootTable;
class UActionManager;
class UAction;

/**
 * Holds all the loot tables for later use
 */
UCLASS()
class BATTLETANKS_API ULootManager : public UObject
{
	GENERATED_BODY()
	
public:
	// Default Constructor
	ULootManager();

	// Get action from the table associated with the provided name
	UAction* GetLoot(FString TableName);

	// Sets the action manager for a local reference
	void SetActionManager(UActionManager* ActionManagerToSet);

private:

	// The map holding all references to the loot tables
	TMap<FString, ULootTable*> Tables;

	// A local reference of the "empty" action for ease of reference
	UAction* EMPTY;

	// A local reference of the action manager for ease of reference
	UActionManager* ActionManager;

	// Used internally to populate the Tables map
	TMap<FString, ULootTable*> LoadTables();

	// SpawnLootActor Method?
	// Replace UActions for Items with this method?
	// Return Empty on GetLoot if Item is rolled?
};


