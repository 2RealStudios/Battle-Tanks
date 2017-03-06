

#pragma once

#include "UObject/NoExportTypes.h"
#include "ActionManager.generated.h"

class UItemManager;
class UAction;
class UItem;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UActionManager : public UObject
{
	GENERATED_BODY()


public:
	bool AddActions(UItemManager* ItemManagerToSet);
	UAction* GetAction(FString ActionName);
	UAction* GetEmpty();

private:
	void AddEmpty();
	TMap<FString, UAction*> Actions;
	UAction* EMPTY;
	UItemManager* ItemManager;
	void AddSpawnAction(FString ActionName, UItem* Item);
	
};
