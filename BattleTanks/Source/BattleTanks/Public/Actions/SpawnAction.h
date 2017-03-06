

#pragma once

#include "Action.h"
#include "SpawnAction.generated.h"

class UItem;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API USpawnAction : public UAction
{
	GENERATED_BODY()

public:
	UItem* ItemToSpawn;


	virtual void doAction(AActor* ActorCalling) override;

	
	
};
