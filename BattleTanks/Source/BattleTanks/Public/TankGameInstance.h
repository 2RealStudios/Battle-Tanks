

#pragma once

#include "Engine/GameInstance.h"
#include "TankGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UTankGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	virtual void  Init() override;
	
	
};
