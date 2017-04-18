

#pragma once

#include "Engine/GameInstance.h"
#include "TankGameInstance.generated.h"

class ULootManager;
class UActionManager;
class UItemManager;
class UModelManager;
class USoundManager;
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
	USoundManager* GetSoundManager();

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

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	USoundManager* SoundManager;
};
