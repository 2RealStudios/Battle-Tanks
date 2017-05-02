

#pragma once

#include "UObject/NoExportTypes.h"
#include "JsonComponent.generated.h"

/**
 * Holds the data need to create a StaticMeshComponent for a JsonModel
 */
UCLASS()
class BATTLETANKS_API UJsonComponent : public UObject
{
	GENERATED_BODY()
	
public:

	// The component this one is extends, Empty if no parent
	UPROPERTY()
	FString Parent = FString();

	// The name of the StaticMeshComponent that this will create
	UPROPERTY()
	FString Name = FString();

	// The path (or identifier) to the mesh for this component
	UPROPERTY()
	FString Path = FString();

	// The path (or identifier) of materials and the indexes they need to be set to for this component
	UPROPERTY()
	TMap<int32, FString> Materials;

	// The scale that this mesh will to have
	UPROPERTY()
	FVector Scale = FVector(1);

	// The rotation that this mesh will to have
	UPROPERTY()
	FRotator Rotation = FRotator(0);

	// The relative location to this component's parent component#
	UPROPERTY()
	FVector Location = FVector(0);

	// The component this component will attach to, defaults to root
	UPROPERTY()
	FString ParentComponent = FString();

	// The socket this component will attach to, defaults to not attaching to a socket
	UPROPERTY()
	FString ParentSocket = FString();

	// Creates a clone of this component
	UJsonComponent* Clone();
	
};
