

#include "BattleTanks.h"
#include "JsonComponent.h"


UJsonComponent* UJsonComponent::Clone()
{
	UJsonComponent* Clone = NewObject<UJsonComponent>(); // Create new component

	// Set information to same as this. Strings are not copied as they should not be changed just set
	Clone->Parent = Parent;
	Clone->Name = Name;
	Clone->Path = Path;
	Clone->Materials= TMap<int32, FString>(Materials); // This creates a copy so that if one map is changed the other doesn't
	Clone->Scale = FVector(Scale); // This creates a copy so that if one vector is changed (possibly by actor?) the other doesn't
	Clone->Rotation = FRotator(Rotation);  // This creates a copy so that if one rotator is changed (possibly by actor?) the other doesn't
	Clone->Location = FVector(Location);
	Clone->ParentComponent = ParentComponent;
	Clone->ParentSocket = ParentSocket;

	return Clone;
}




