

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

protected:
	virtual void  Init() override;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	ULootManager* LootManager;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UActionManager* ActionManager;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UItemManager* ItemManager;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	UModelManager* ModelManager;
};
