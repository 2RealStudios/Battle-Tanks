

#pragma once

#include "UObject/NoExportTypes.h"
#include "LootManager.generated.h"

class ULootTable;
class UActionManager;
class UAction;
class UTankGameInstance;

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
	
	void Init(UTankGameInstance* GameInstance);

private:

	// The map holding all references to the loot tables
	UPROPERTY()
	TMap<FString, ULootTable*> Tables;

	// A local reference of the "empty" action for ease of reference
	UPROPERTY()
		UAction* EMPTY;

	// A local reference of the action manager for ease of reference
	UPROPERTY()
		UActionManager* ActionManager;

	// Used internally to populate the Tables map
	TMap<FString, ULootTable*> LoadTables();

	// SpawnLootActor Method?
	// Replace UActions for Items with this method?
	// Return Empty on GetLoot if Item is rolled?
};


