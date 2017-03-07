

#include "BattleTanks.h"
#include "Item/Item.h"
#include "Item/ItemFuel.h"
#include "Item/ItemAmmo.h"
#include "ItemManager.h"

UItemManager::UItemManager()
{
	Items = AddItems();
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

UItem* UItemManager::GetNullItem()
{
	return NULL_ITEM;
}

TMap<FString, UItem*> UItemManager::AddItems()
{
	TMap<FString, UItem*> Items;
	NULL_ITEM = NewObject<UItem>();
	Items.Add(FString("null"), NULL_ITEM);

	int amounts[] = {1, 5, 10, 20};

	for (int amount : amounts)
	{
		auto Fuel = NewObject<UItemFuel>();
		Fuel->Amount = amount;
		Items.Add(FString("fuel") + FString::FromInt(amount), Fuel);
		
		auto Ammo = NewObject<UItemAmmo>();
		Ammo->Amount = amount;
		Items.Add(FString("ammo") + FString::FromInt(amount), Ammo);
	}
	return Items;

}