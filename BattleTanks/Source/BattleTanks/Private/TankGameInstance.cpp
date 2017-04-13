

#include "BattleTanks.h"
#include "Item/ItemManager.h"
#include "LootManager.h"
#include "ActionManager.h"
#include "Model/ModelManager.h"
#include "TankGameInstance.h"


UTankGameInstance::UTankGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("Custom Game Instance Created"))
	ItemManager = NewObject<UItemManager>();
	ModelManager = NewObject<UModelManager>();
	LootManager = NewObject<ULootManager>();
	ActionManager = NewObject<UActionManager>();
}

void  UTankGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Custom Game Instance::Init()"))
	
	ItemManager->Init(this);
	ActionManager->Init(this);
	LootManager->Init(this);
	ModelManager->Init(this);
}

UModelManager* UTankGameInstance::GetModelManager()
{
	return ModelManager;
}

ULootManager* UTankGameInstance::GetLootManager()
{
	return LootManager;
}

UActionManager* UTankGameInstance::GetActionManager()
{
	return ActionManager;
}

UItemManager* UTankGameInstance::GetItemManager()
{
	return ItemManager;
}
