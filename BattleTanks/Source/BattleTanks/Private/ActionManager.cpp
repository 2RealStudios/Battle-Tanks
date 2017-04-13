

#include "BattleTanks.h"
#include "Action.h"
#include "Actions/SpawnAction.h"
#include "Item/ItemManager.h"
#include "Item/Item.h"
#include "TankGameInstance.h"
#include "ActionManager.h"


void UActionManager::Init(UTankGameInstance* GameInstance)
{
	AddActions(GameInstance->GetItemManager());
}

bool UActionManager::AddActions(UItemManager* ItemManagerToSet)
{
	UE_LOG(LogTemp, Warning, TEXT("Adding Actions"))

	ItemManager = ItemManagerToSet;
	
	AddEmpty();

	int amounts[] = { 1, 5, 10, 20 };

	for (int amount : amounts)
	{
		FString FuelName = FString("fuel") + FString::FromInt(amount);
		AddSpawnAction(FuelName, ItemManager->GetItem(FuelName));

		FString AmmoName = FString("ammo") + FString::FromInt(amount);
		AddSpawnAction(AmmoName, ItemManager->GetItem(AmmoName));
	}
	
	return true;
}

UAction* UActionManager::GetAction(FString ActionName)
{
	if (Actions.Contains(ActionName))
	{
		return Actions[ActionName];
	}
	UE_LOG(LogTemp, Warning, TEXT("UAction for %s not found defaulting to EMPTY"), *ActionName)

	return EMPTY;

}

UAction* UActionManager::GetEmpty()
{
	return EMPTY;
}

void UActionManager::AddEmpty()
{
	EMPTY = NewObject<UAction>();
	Actions.Add(FString("empty"), EMPTY);
}

void UActionManager::AddSpawnAction(FString ActionName, UItem* Item)
{
	if (Item == ItemManager->GetNullItem())
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to add a spawn action for: %s"), *ActionName)
		return;
	}
	auto SpawnActor = NewObject<USpawnAction>();
	SpawnActor->ItemToSpawn = Item;
	this->Actions.Add(ActionName, SpawnActor);
}
