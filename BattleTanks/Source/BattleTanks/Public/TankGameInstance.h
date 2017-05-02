

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
	
	// Get the Loot Manager
	ULootManager* GetLootManager();

	// Get the Action Manager
	UActionManager* GetActionManager();
	
	// Get the Item Manager
	UItemManager* GetItemManager();
	
	// Get the Model Manager
	UModelManager* GetModelManager();
	
	// Get the Sound Manager
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
