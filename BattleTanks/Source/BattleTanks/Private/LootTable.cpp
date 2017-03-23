

#include "BattleTanks.h"
#include "LootTable.h"

ULootTableEntry* ULootTable::GetLoot()
{
	int32 randomNumber = FMath::RandRange(0 , TotalWeight);
	int32 weight = 0;
	for (auto entry: table) 
	{
		weight += entry->weight;
		if (randomNumber <= weight) {
			return entry;
		}
	}
	return nullptr; // HOW? SHOULD NOT BE POSSIBLE

}


bool ULootTable::loadFromFile(FString fileLocation)
{
	FString JsonString;

	if (FFileHelper::LoadFileToString(JsonString, *fileLocation))
	{
		TSharedRef< TJsonReader<TCHAR> > Reader = TJsonReaderFactory<TCHAR>::Create(JsonString);
		TArray<TSharedPtr<FJsonValue>> JsonObjectPtr;
		
		if (FJsonSerializer::Deserialize(Reader, JsonObjectPtr))
		{
			for (auto &entry : JsonObjectPtr)
			{
				ULootTableEntry* entryToAdd = NewObject<ULootTableEntry>();
				TSharedPtr<FJsonObject> JsonObject = entry->AsObject();

				FString name;
				double dWeight;	

				if (!JsonObject->TryGetNumberField("weight", dWeight))
				{
					dWeight = 1;
				}

				int32 weight = FPlatformMath::RoundToInt(dWeight);

				if (JsonObject->TryGetStringField(FString("name"), name))
				{
					entryToAdd->name = name;
					entryToAdd->weight = weight;
					table.Add(entryToAdd);
					TotalWeight += weight;
				}
			}
			return table.Num() > 0;
		}
	}

	return false;
}




