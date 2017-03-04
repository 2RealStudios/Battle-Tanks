

#pragma once

#include "Engine/GameInstance.h"
#include "TankGameInstance.generated.h"

class ULootManager;
class UActionManager;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UTankGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UTankGameInstance();

	ULootManager* GetLootManager();
	UActionManager* GetActionManager();

private:
	virtual void  Init() override;
	ULootManager* LootManager;
	UActionManager* ActionManager;
};
