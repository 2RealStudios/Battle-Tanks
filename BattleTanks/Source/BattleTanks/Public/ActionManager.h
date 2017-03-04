

#pragma once

#include "UObject/NoExportTypes.h"
#include "ActionManager.generated.h"

class UAction;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UActionManager : public UObject
{
	GENERATED_BODY()


public:
	bool AddActions();
	UAction* GetAction(FString ActionName);
	UAction* GetEmpty();

private:
	void AddEmpty();
	TMap<FString, UAction*> Actions;
	UAction* EMPTY;
	
	
};
