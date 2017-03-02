

#include "BattleTanks.h"
#include "TankGameInstance.h"
#include "LootTable.h"


void  UTankGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Custom Game Instance::Init()"))
	IFileManager& FileManager = IFileManager::Get();
	TArray<FString> files;

	FString gameDir = FPaths::GameContentDir() +"/Loot/";
	FString ext = FString("*.json");
	FileManager.FindFiles(files, *gameDir,*ext);
	for (auto& Str : files) 
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Str)
		ULootTable* table = NewObject<ULootTable>();
		table->loadFromFile(gameDir + Str);
	}
}
