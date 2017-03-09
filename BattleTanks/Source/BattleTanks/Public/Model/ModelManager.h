

#pragma once

#include "UObject/NoExportTypes.h"
#include "Model/JsonModel.h"
#include "ModelManager.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UModelManager : public UObject
{
	GENERATED_BODY()

public:
	UModelManager();
	TMap<FString, UJsonModel*> LoadModels();
	UJsonModel* GetModel(FString ModelName);
	void PreLoadModelAssets();

private:
	TMap<FString, UJsonModel*> Models;
	UJsonModel* EMPTY;


};
