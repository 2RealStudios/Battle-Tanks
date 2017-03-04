

#include "BattleTanks.h"
#include "LootManager.h"
#include "ActionManager.h"
#include "TankGameInstance.h"

UTankGameInstance::UTankGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("Custom Game Instance Created"))
}

void  UTankGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Custom Game Instance::Init()"))

	ActionManager = NewObject<UActionManager>();
	ActionManager->AddActions();

	LootManager = NewObject<ULootManager>();
	LootManager->SetActionManager(ActionManager);

	UAction* Loot = LootManager->GetLoot(FString("zombie1"));
	if (Loot)
	{
		UE_LOG(LogTemp,Warning, TEXT("Successfully got loot"))
	}
}


ULootManager* UTankGameInstance::GetLootManager()
{
	return LootManager;
}

UActionManager* UTankGameInstance::GetActionManager()
{
	return ActionManager;
}
