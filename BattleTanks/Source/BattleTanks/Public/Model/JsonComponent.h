

#pragma once

#include "UObject/NoExportTypes.h"
#include "JsonComponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API UJsonComponent : public UObject
{
	GENERATED_BODY()
	
public:
	FString Name = FString();
	FString Path = FString();
	TMap<int32, FString> Materials;
	FVector Scale = FVector(1);
	FRotator Rotation = FRotator(0);
	FVector Location = FVector(0);
	FString ParentComponent = FString();
	FString ParentSocket = FString();

	
	
};
