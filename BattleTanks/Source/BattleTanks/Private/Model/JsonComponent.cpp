

#include "BattleTanks.h"
#include "JsonComponent.h"


UJsonComponent* UJsonComponent::Clone()
{
	UJsonComponent* Clone = NewObject<UJsonComponent>();

	Clone->Parent = Parent;
	Clone->Name = Name;
	Clone->Path = Path;
	Clone->Materials= TMap<int32, FString>(Materials);
	Clone->Scale = FVector(Scale);
	Clone->Rotation = FRotator(Rotation);
	Clone->Location = FVector(Location);
	Clone->ParentComponent = ParentComponent;
	Clone->ParentSocket = ParentSocket;

	return Clone;
}




