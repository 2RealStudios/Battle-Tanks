

#pragma once

#include "UObject/NoExportTypes.h"
#include "ActionManager.generated.h"

class UItemManager;
class UAction;
class UItem;

/**
 * Holds all the actions for later use
 */
UCLASS()
class BATTLETANKS_API UActionManager : public UObject
{
	GENERATED_BODY()


public:
	/* 
		Add Actions to the Actions map, needs ItemManager so the spawn actions can be created
		TODO? remove this prameter
	*/
	bool AddActions(UItemManager* ItemManagerToSet);

	// Get the action associated with the provided name. Returns a "empty" action if the name does not have an action associated with it
	UAction* GetAction(FString ActionName);

	// Get the "empty" action reference
	UAction* GetEmpty();

private:

	// Handles adding the "empty" action to the Actions map and setting the variable for it
	void AddEmpty();

	// The map holding all references to the actions future?:(except for spawning actions)
	UPROPERTY()
	TMap<FString, UAction*> Actions;

	// The reference to the "empty" action
	UPROPERTY()
	UAction* EMPTY;

	// The local reference to the Item Manager for this manager to use
	UPROPERTY()
	UItemManager* ItemManager;

	// A helper method to register a spawn action
	void AddSpawnAction(FString ActionName, UItem* Item);
	
};
