

#pragma once

#include "UObject/NoExportTypes.h"
#include "LootManager.generated.h"

class ULootTable;
class UActionManager;
class UAction;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ULootManager : public UObject
{
	GENERATED_BODY()
	
public:
	ULootManager();
	TMap<FString, ULootTable*> LoadTables();
	UAction* GetLoot(FString TableName);
	void SetActionManager(UActionManager* ActionManagerToSet);

private:
	TMap<FString, ULootTable*> Tables;
	UAction* EMPTY;
	UActionManager* ActionManager;
};


