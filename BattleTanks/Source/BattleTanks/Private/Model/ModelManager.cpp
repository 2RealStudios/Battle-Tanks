

#include "BattleTanks.h"
#include "ModelManager.h"

UModelManager::UModelManager()
{
	EMPTY = NewObject<UJsonModel>();
	Models = LoadModels();
}

TMap<FString, UJsonModel*> UModelManager::LoadModels()
{
	TMap<FString, UJsonModel*> mModel;

	UE_LOG(LogTemp, Warning, TEXT("Loading Models"))
		IFileManager& FileManager = IFileManager::Get();
	TArray<FString> files;

	FString gameDir = FPaths::GameContentDir() + "/Model/";
	FString ext = TEXT("*.json");
	FileManager.FindFiles(files, *gameDir, *ext);
	for (auto& FileName : files)
	{
		UJsonModel* model = NewObject<UJsonModel>();
		model->LoadFromFile(gameDir + FileName);

		FString ModelName = FString(FileName);
		ModelName.RemoveFromEnd(FString(".json"));

		mModel.Add(ModelName, model);
	}
	return mModel;
}

UJsonModel* UModelManager::GetModel(FString ModelName)
{
	if (Models.Contains(ModelName))
		return Models[ModelName];
	return EMPTY;
}

void  UModelManager::PreLoadModelAssets()
{
	UE_LOG(LogTemp, Warning, TEXT("Preloading Models"))
	for (auto& Entry : Models)
	{
		Entry.Value->PreLoad();
	}
}



