

#pragma once

#include "Action.h"
#include "SpawnAction.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API USpawnAction : public UAction
{
	GENERATED_BODY()

public:
	virtual void doAction(AActor* ActorCalling) override;

	
	
};
