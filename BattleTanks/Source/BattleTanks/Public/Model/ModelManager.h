

#pragma once

#include "UObject/NoExportTypes.h"
#include "Model/JsonModel.h"
#include "ModelManager.generated.h"

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
	UJsonModel* GetModel(FString ModelName);

	// Preload the model assets (mesh, materials, etc.) so there is no delay when the model is being used
	void PreloadModelAssets();

private:
	// The map holding all references to the mdoels
	TMap<FString, UJsonModel*> Models;

	// A blank model to default to in case a model is requested for a name that doesn't exist
	UJsonModel* EMPTY;

	// Used internally to populate the Models map with models
	TMap<FString, UJsonModel*> LoadModels();


};
