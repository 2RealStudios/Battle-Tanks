

#pragma once

#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

/**
 * A base class to hand actions that the loot system can roll
 * i.e. spawn an item, create an explostion, etc.
 */
UCLASS()
class BATTLETANKS_API UAction : public UObject
{
	GENERATED_BODY()

public:
	// Preform the action that the provided Actor happened to get
	virtual void doAction(AActor* ActorCalling);
	
	
};
