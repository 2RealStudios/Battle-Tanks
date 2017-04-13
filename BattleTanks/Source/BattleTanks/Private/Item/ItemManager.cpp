

#include "BattleTanks.h"
#include "Item/Item.h"
#include "Item/ItemFuel.h"
#include "Item/ItemAmmo.h"
#include "TankGameInstance.h"
#include "ItemManager.h"

UItemManager::UItemManager()
{
}


UItem* UItemManager::GetItem(FString ItemName)
{
	ItemName = ItemName.ToLower();

	if (Items.Contains(ItemName))
	{
		return Items[ItemName];
	}
	return GetNullItem();
}

void UItemManager::Init(UTankGameInstance* GameInstance)
{
	Items = AddItems();
}

UItem* UItemManager::GetNullItem()
{
	return NULL_ITEM;
}

FString UItemManager::GetItemName(UItem* Item)
{
	const FString* ret = Items.FindKey(Item);
	if (ret)
	{
		return *ret;
	}
	return FString("empty");
}

TMap<FString, UItem*> UItemManager::AddItems()
{
	UE_LOG(LogTemp, Warning, TEXT("Adding Items"))

	TMap<FString, UItem*> Items;
	NULL_ITEM = NewObject<UItem>();
	Items.Add(FString("empty"), NULL_ITEM);

	int FuelAmounts[] = {5, 25, 50, 100};

	for (int amount : FuelAmounts)
	{
		auto Fuel = NewObject<UItemFuel>();
		Fuel->Amount = amount;
		Items.Add(FString("fuel") + FString::FromInt(amount), Fuel);
		
		
	}

	int AmmoAmounts[] = {1, 5, 10, 20};

	for (int amount : AmmoAmounts)
	{
		auto Ammo = NewObject<UItemAmmo>();
		Ammo->Amount = amount;
		Items.Add(FString("ammo") + FString::FromInt(amount), Ammo);
	}

	return Items;

}