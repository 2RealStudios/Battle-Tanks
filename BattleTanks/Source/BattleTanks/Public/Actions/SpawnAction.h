

#pragma once

#include "Action.h"
#include "SpawnAction.generated.h"

class UItem;

/**
 * An action whose soul purpose is to spawn the designated Item in to the world
 */
UCLASS()
class BATTLETANKS_API USpawnAction : public UAction
{
	GENERATED_BODY()

public:
	// The item that will be spawned in to the world
	UItem* ItemToSpawn;

	// Preform the action that the provided Actor happened to get The AActor 
	virtual void doAction(AActor* ActorCalling) override;

	
	
};
