

#include "BattleTanks.h"
#include "Action.h"
#include "Actions/SpawnAction.h"
#include "Item/ItemManager.h"
#include "Item/Item.h"
#include "ActionManager.h"

bool UActionManager::AddActions(UItemManager* ItemManagerToSet)
{
	UE_LOG(LogTemp, Warning, TEXT("Adding Actions"))

	ItemManager = ItemManagerToSet;

	try
	{
		AddEmpty();

		int amounts[] = { 1, 5, 10, 20 };

		for (int amount : amounts)
		{
			FString ActionName = FString("fuel") + FString::FromInt(amount);
			AddSpawnAction(ActionName, ItemManager->GetItem(ActionName));
		}
	}
	catch (const std::exception&)
	{
		UE_LOG(LogTemp, Warning, TEXT("Didn't work"))
		return false;
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
