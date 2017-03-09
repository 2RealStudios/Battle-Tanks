

#include "BattleTanks.h"
#include "Item/ItemManager.h"
#include "LootManager.h"
#include "ActionManager.h"
#include "Model/ModelManager.h"
#include "TankGameInstance.h"


UTankGameInstance::UTankGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("Custom Game Instance Created"))
}

void  UTankGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Custom Game Instance::Init()"))

	ItemManager = NewObject<UItemManager>();

	ActionManager = NewObject<UActionManager>();
	ActionManager->AddActions(ItemManager);

	LootManager = NewObject<ULootManager>();
	LootManager->SetActionManager(ActionManager);

	ModelManager = NewObject<UModelManager>();
	ModelManager->PreloadModelAssets();
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
