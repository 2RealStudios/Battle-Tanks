

#pragma once

#include "UObject/NoExportTypes.h"
#include "Model/JsonModel.h"
#include "ModelManager.generated.h"

class UTankGameInstance;

/**
 * Holds all the models for later use
 */
UCLASS()
class BATTLETANKS_API UModelManager : public UObject
{
	GENERATED_BODY()

public:
	// Default Constructor
	UModelManager();

	// Get the model associated with the provided name 
	UFUNCTION(BlueprintCallable, Category = "Model")
	UJsonModel* GetModel(FString ModelName);

	// Preload the model assets (mesh, materials, etc.) so there is no delay when the model is being used
	void PreloadModelAssets();

	void Init(UTankGameInstance* GameInstance);
private:
	// The map holding all references to the mdoels
	UPROPERTY()
	TMap<FString, UJsonModel*> Models;

	// A blank model to default to in case a model is requested for a name that doesn't exist
	UPROPERTY()
	UJsonModel* EMPTY;

	// Used internally to populate the Models map with models
	TMap<FString, UJsonModel*> LoadModels();
};
