

#pragma once

#include "UObject/NoExportTypes.h"
#include "Action.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UAction : public UObject
{
	GENERATED_BODY()
public:
	virtual void doAction(AActor* ActorCalling);
	
	
};
