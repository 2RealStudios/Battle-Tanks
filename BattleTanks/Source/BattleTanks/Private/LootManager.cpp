

#include "BattleTanks.h"
#include "LootTable.h"
#include "Action.h"
#include "ActionManager.h"
#include "TankGameInstance.h"
#include "LootManager.h"

ULootManager::ULootManager()
{
}

void ULootManager::Init(UTankGameInstance* GameInstance)
{
	Tables = LoadTables();
	SetActionManager(GameInstance->GetActionManager());
}


TMap<FString, ULootTable*> ULootManager::LoadTables()
{
	TMap<FString, ULootTable*> mTables;

	UE_LOG(LogTemp, Warning, TEXT("Loading LootTables"))
	IFileManager& FileManager = IFileManager::Get();
	TArray<FString> files;

	FString gameDir = FPaths::GameContentDir() + "/Loot/";
	FString ext = TEXT("*.json");
	FileManager.FindFiles(files, *gameDir, *ext);
	for (auto& FileName : files)
	{
		ULootTable* table = NewObject<ULootTable>();
		table->loadFromFile(gameDir + FileName);

		FString TableName = FString(FileName);
		TableName.RemoveFromEnd(FString(".json"));

		mTables.Add(TableName, table);
	}
	return mTables;
}

void ULootManager::SetActionManager(UActionManager* ActionManagerToSet)
{
	ActionManager = ActionManagerToSet;
	EMPTY = ActionManager->GetEmpty();
}

UAction* ULootManager::GetLoot(FString TableName)
{
	FString NextToLookUp = FString(TableName);
	bool isTable = true;

	//Use while loop over recursion to hopefully cut down on memory use 
	while (isTable)
	{
		isTable = false;

		if (!Tables.Contains(NextToLookUp))
		{
			return EMPTY;
		}

		ULootTable* table = (Tables)[NextToLookUp];
		FString loot = table->GetLoot()->name;
		
		if (loot.StartsWith(FString("loot:")))
		{
			isTable = true;
			NextToLookUp = FString(loot);
			NextToLookUp.RemoveFromStart(FString("loot:"));
		}
		else
		{
			return ActionManager->GetAction(loot);
		}
	}

	return EMPTY;
}
