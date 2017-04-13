

#pragma once

#include "UObject/NoExportTypes.h"
#include "ItemManager.generated.h"

class UItem;
class UTankGameInstance;

/**
 * Holds all the items for later use 
 */
UCLASS()
class BATTLETANKS_API UItemManager : public UObject
{
	GENERATED_BODY()
	
public:
	// Default Constructor
	UItemManager();

	// Get the item associated with the provided name. Returns a "null" item if the name does not have an item associated with it
	UItem* GetItem(FString ItemName);

	// Gets the "null" item
	UItem* GetNullItem();

	// Gets the name associated with the passed item
	FString GetItemName(UItem* Item);

	void Init(UTankGameInstance* GameInstance);

private:

	// The map holding all references to the items
	UPROPERTY()
	TMap<FString, UItem*> Items;

	// The "null" item
	UItem* NULL_ITEM;

	// Used internally to populate the Items map with items
	TMap<FString, UItem*> AddItems();

};
