

#pragma once

#include "UObject/NoExportTypes.h"
#include "ItemManager.generated.h"

class UItem;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API UItemManager : public UObject
{
	GENERATED_BODY()
	
public:
	UItemManager();
	UItem* GetItem(FString ItemName);
	UItem* GetNullItem();
	FString GetItemName(UItem* Item);

private:
	TMap<FString, UItem*> Items;
	UItem* NULL_ITEM;
	TMap<FString, UItem*> AddItems();
};
