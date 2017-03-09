

#pragma once

#include "Engine/GameInstance.h"
#include "TankGameInstance.generated.h"

class ULootManager;
class UActionManager;
class UItemManager;
class UModelManager;

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
	UItemManager* GetItemManager();
	UModelManager* GetModelManager();
private:
	virtual void  Init() override;
	ULootManager* LootManager;
	UActionManager* ActionManager;
	UItemManager* ItemManager;
	UModelManager* ModelManager;
};
