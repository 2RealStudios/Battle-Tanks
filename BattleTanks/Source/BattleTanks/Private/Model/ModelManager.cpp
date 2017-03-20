

#include "BattleTanks.h"
#include "ModelManager.h"

UModelManager::UModelManager()
{
	EMPTY = NewObject<UJsonModel>(); // Create empty model as a default
	EMPTY->Name = FString("EMPTY");

	Models = LoadModels(); // Load models and set them to get around an annoying bug
}

TMap<FString, UJsonModel*> UModelManager::LoadModels()
{
	TMap<FString, UJsonModel*> mModel; // Holds all models created

	UE_LOG(LogTemp, Warning, TEXT("Loading Models"))

	IFileManager& FileManager = IFileManager::Get();  // Get file manager to read files

	TArray<FString> files; // Files in the /Content/Model/ directory

	FString gameDir = FPaths::GameContentDir() + "/Model/"; // Directory to check
	FString ext = TEXT("*.json"); // Extention to find
	FileManager.FindFiles(files, *gameDir, *ext); // Find all files that match
	for (auto& FileName : files)
	{
		UJsonModel* model = NewObject<UJsonModel>(); // Create model
		model->LoadFromFile(gameDir + FileName); // Give it the file to load from

		FString ModelName = FString(FileName); // Create model name
		ModelName.RemoveFromEnd(FString(".json"));

		model->Name = ModelName; // Set model name

		mModel.Add(ModelName, model); // Add model to map
	}

	// Return the map of models
	return mModel;
}

UJsonModel* UModelManager::GetModel(FString ModelName)
{
	if (Models.Contains(ModelName)) // Check if model exists and return it
		return Models[ModelName];
	return EMPTY; // Return empty if not present
}

void  UModelManager::PreloadModelAssets()
{
	UE_LOG(LogTemp, Warning, TEXT("Preloading Models Assets"))
	
	TSet<FString> MeshesToLoad; // The meshes to load
	TSet<FString> MaterialToLoad; // The materials to load
	
	for (auto& Entry : Models) // Get all meshes and materials from all the models
	{
		Entry.Value->PreloadAssets(MeshesToLoad, MaterialToLoad); 
	}

	for (auto Mesh : MeshesToLoad) // Load every mesh
	{
		UE_LOG(LogTemp, Warning, TEXT("\tPreloading %s"), *Mesh)
		UJsonModel::GetStaticMesh(FName(*Mesh));
	}

	for (auto Material : MaterialToLoad) // Load every material
	{
		UE_LOG(LogTemp, Warning, TEXT("\tPreloading %s"), *Material)
		UJsonModel::GetMaterial(FName(*Material));
	}

	// TODO experiment with holding these references and using them in models... Save time on model creation?
}



