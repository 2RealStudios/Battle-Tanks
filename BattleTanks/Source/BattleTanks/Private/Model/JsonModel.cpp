

#include "BattleTanks.h"
#include "LootActor.h"
#include "TankGameInstance.h"
#include "Model/ModelManager.h"
#include "JsonModel.h"


void UJsonModel::LoadFromFile(FString FileName)
{
	FString JsonString;

	if (FFileHelper::LoadFileToString(JsonString, *FileName))
	{
		TSharedRef< TJsonReader<TCHAR> > Reader = TJsonReaderFactory<TCHAR>::Create(JsonString);
		TSharedPtr<FJsonObject> JsonObjectPtr;

		if (FJsonSerializer::Deserialize(Reader, JsonObjectPtr))
		{

			if (JsonObjectPtr->HasField(FString("parent")))
			{
				Parent = JsonObjectPtr->GetStringField(FString("parent"));
			}

			if (JsonObjectPtr->HasField(FString("materials")))
			{
				TArray<TSharedPtr<FJsonValue>> MaterialArray = JsonObjectPtr->GetArrayField(FString("materials"));
				for (auto MaterialValue : MaterialArray)
				{
					TSharedPtr<FJsonObject> MaterialObject = MaterialValue->AsObject();
					if (MaterialObject->HasField(FString("name")) && MaterialObject->HasField(FString("path")))
					{
						auto MaterialName = MaterialObject->GetStringField(FString("name"));
						auto MaterialPath = MaterialObject->GetStringField(FString("path"));

						Materials.Add(MaterialName, MaterialPath);
					}
				}

			}

			if (JsonObjectPtr->HasField(FString("meshes")))
			{
				TArray<TSharedPtr<FJsonValue>> MeshArray = JsonObjectPtr->GetArrayField(FString("meshes"));
				for (auto MeshValue : MeshArray)
				{
					TSharedPtr<FJsonObject> MeshObject = MeshValue->AsObject();
					if (MeshObject->HasField(FString("name")) && MeshObject->HasField(FString("path")))
					{
						auto MeshName = MeshObject->GetStringField(FString("name"));
						auto MeshPath = MeshObject->GetStringField(FString("path"));

						Meshes.Add(MeshName, MeshPath);
					}
				}

			}
			if (JsonObjectPtr->HasField(FString("components")))
			{
				TArray<TSharedPtr<FJsonValue>> ComponentArray = JsonObjectPtr->GetArrayField(FString("components"));
				for (auto MeshValue : ComponentArray)
				{
					TSharedPtr<FJsonObject> ComponentObject = MeshValue->AsObject();
					UJsonComponent* Component = NewObject<UJsonComponent>();
					Component->Name = ComponentObject->GetStringField(FString("name"));
					Component->Path = ComponentObject->GetStringField(FString("path"));

					for (auto MaterialValue : ComponentObject->GetArrayField(FString("materials")))
					{
						auto MaterialObject = MaterialValue->AsObject();
						auto MaterialIndex = MaterialObject->GetIntegerField(FString("index"));
						auto MaterialPath = MaterialObject->GetStringField(FString("path"));

						Component->Materials.Add(MaterialIndex, MaterialPath);
					}

					if (ComponentObject->HasField(FString("scale")))
					{
						FVector ScaleToSet = FVector(0);
						auto ScaleValues = ComponentObject->GetArrayField(FString("scale"));
						ScaleToSet.X = ScaleValues[0]->AsNumber();
						ScaleToSet.Y = ScaleValues[1]->AsNumber();
						ScaleToSet.Z = ScaleValues[2]->AsNumber();

						Component->Scale = ScaleToSet;
					}

					if (ComponentObject->HasField(FString("rotation")))
					{
						FRotator RotationToSet = FRotator(0);
						auto ScaleValues = ComponentObject->GetArrayField(FString("scale"));
						RotationToSet.Pitch = ScaleValues[0]->AsNumber();
						RotationToSet.Yaw = ScaleValues[1]->AsNumber();
						RotationToSet.Roll = ScaleValues[2]->AsNumber();

						Component->Rotation = RotationToSet;
					}

					if (ComponentObject->HasField(FString("location")))
					{
						FVector LocationToSet = FVector(0);
						auto LocationValues = ComponentObject->GetArrayField(FString("location"));
						LocationToSet.X = LocationValues[0]->AsNumber();
						LocationToSet.Y = LocationValues[1]->AsNumber();
						LocationToSet.Z = LocationValues[2]->AsNumber();

						Component->Location = LocationToSet;
					}

					if (ComponentObject->HasField(FString("parentComponent")))
					{
						Component->ParentComponent = ComponentObject->GetStringField(FString("parentComponent"));
						if (ComponentObject->HasField(FString("parentSocket")))
						{
							Component->ParentSocket = ComponentObject->GetStringField(FString("parentSocket"));
						}
					}

					Components.Add(Component->Name, Component);
				}
			}
		}
			
	}


}

void UJsonModel::PreLoad()
{
	TSet<FString> LoadedObjects;
	TArray<FString> ObjectsToPreLoad;
	
	Meshes.GenerateValueArray(ObjectsToPreLoad);
	for (auto Mesh : ObjectsToPreLoad)
	{
		if (!LoadedObjects.Contains(Mesh))
		{
			UE_LOG(LogTemp, Warning, TEXT("\tPreloading %s"), *Mesh)
			GetStaticMesh(FName(*Mesh)); 
			LoadedObjects.Add(Mesh);
		}
	}

	Materials.GenerateValueArray(ObjectsToPreLoad);
	for (auto Material : ObjectsToPreLoad)
	{
		if (!LoadedObjects.Contains(Material))
		{
			UE_LOG(LogTemp, Warning, TEXT("\tPreloading %s"), *Material)
			GetMaterial(FName(*Material));
			LoadedObjects.Add(Material);
		}
	}


	TArray<UJsonComponent*> ComponentsToLoad;

	Components.GenerateValueArray(ComponentsToLoad);

	for (UJsonComponent* Component : ComponentsToLoad)
	{
		FString Mesh = Component->Path;

		if (!Mesh.StartsWith(FString("$"))) 
		{
			if (!LoadedObjects.Contains(Mesh))
			{
				UE_LOG(LogTemp, Warning, TEXT("\tPreloading %s"), *Mesh)
				GetStaticMesh(FName(*Mesh));
				LoadedObjects.Add(Mesh);
			}
		}

		Component->Materials.GenerateValueArray(ObjectsToPreLoad);
		for (auto Material : ObjectsToPreLoad)
		{
			if (!Material.StartsWith(FString("$"))) 
			{
				if (!LoadedObjects.Contains(Material))
				{
					UE_LOG(LogTemp, Warning, TEXT("\tPreloading %s"), *Material)
					GetMaterial(FName(*Material));
					LoadedObjects.Add(Material);
				}
			}
		}
	}
}


void UJsonModel::AttachToLootActor(ALootActor* Actor)
{
	TMap<FString, USceneComponent*> AddedComponents;
	TArray<UJsonComponent*> ComponentsToAdd;

	UJsonModel* CompositeModel = BuildCompositeModel(Cast<UTankGameInstance>(Actor->GetWorld()->GetGameInstance()));


	CompositeModel->Components.GenerateValueArray(ComponentsToAdd);
	while (ComponentsToAdd.Num() > 0)
	{
		TArray<int32> ToRemove;
		for (auto It = ComponentsToAdd.CreateIterator(); It; ++It)
		{
			auto JsonComponent = *It;
			if (JsonComponent->ParentComponent.IsEmpty() || AddedComponents.Contains(JsonComponent->ParentComponent))
			{
				USceneComponent* ComponentToAttachTo = Actor->GetRootComponent();
				if (!JsonComponent->ParentComponent.IsEmpty())
				{
					ComponentToAttachTo = AddedComponents[JsonComponent->ParentComponent];
				}

				FName SocketToAttachTo = NAME_None;
				if (!JsonComponent->ParentSocket.IsEmpty())
				{
					SocketToAttachTo = FName(*JsonComponent->ParentSocket);
				}

				UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(Actor, FName(*JsonComponent->Name));

				if (Mesh)
				{
					Mesh->RegisterComponent();
					Mesh->AttachToComponent(ComponentToAttachTo, FAttachmentTransformRules::KeepRelativeTransform, SocketToAttachTo);
				}

				FString ItemMeshPath = JsonComponent->Path;
				if (ItemMeshPath.StartsWith(FString("$")))
				{
					FString MeshID = FString(ItemMeshPath);
					MeshID.RemoveFromStart(FString("$"));
					if (CompositeModel->Meshes.Contains(MeshID))
					{
						ItemMeshPath = CompositeModel->Meshes[MeshID];
					}
					else
					{
						// TODO Decide Default
					}
				}

				auto ItemMesh = GetStaticMesh(FName(*ItemMeshPath)); // Finds cube static mesh

				if (ItemMesh)
				{
					Mesh->SetStaticMesh(ItemMesh);
					Mesh->SetWorldScale3D(JsonComponent->Scale);
					Mesh->SetRelativeLocationAndRotation(JsonComponent->Location, JsonComponent->Rotation);
					for (auto& MaterialEntry : JsonComponent->Materials)
					{
						FString MaterialPath = MaterialEntry.Value;
						if (MaterialPath.StartsWith(FString("$")))
						{
							FString MaterialID = FString(MaterialPath);
							MaterialID.RemoveFromStart(FString("$"));
							if (CompositeModel->Materials.Contains(MaterialID))
							{
								MaterialPath = CompositeModel->Materials[MaterialID];
							}
							else
							{
								// TODO Decide Default
							}

						}

						auto Material = GetMaterial(FName(*MaterialPath)); // Finds item material

						if (Material)
						{
							Mesh->SetMaterial(MaterialEntry.Key, Material);
						}
					}
					
				}
				else
				{
					//UE_LOG(LogTemp, Warning, TEXT("Unable to find cube?"));
				}

				AddedComponents.Add(JsonComponent->Name, Mesh);
				ToRemove.Add(It.GetIndex());
			}
			else
			{
				// Do Nothing
			}
			for (auto Remove : ToRemove)
			{
				ComponentsToAdd.RemoveAt(Remove);
			}
		}
	}
}



UJsonModel* UJsonModel::BuildCompositeModel(UTankGameInstance* GameInstance)
{
	if (Parent.IsEmpty())
		return Clone();

	if (GameInstance)
	{
		UModelManager* ModelManager = GameInstance->GetModelManager();
		UJsonModel* ParentModel = ModelManager->GetModel(Parent);
		ParentModel = ParentModel->BuildCompositeModel(GameInstance);
		ParentModel->Parent = Parent;
		ParentModel->Materials.Append(Materials);
		ParentModel->Meshes.Append(Meshes);
		ParentModel->Components.Append(Components);

		return ParentModel;
	}

	return NewObject<UJsonModel>(); // Should NEVER Reach
}

UJsonModel* UJsonModel::Clone()
{
	UJsonModel* Clone = NewObject<UJsonModel>();
	Clone->Parent = Parent;
	Clone->Materials = TMap<FString, FString>(Materials);
	Clone->Meshes = TMap<FString, FString>(Meshes);
	Clone->Components= TMap<FString, UJsonComponent*>(Components);

	return Clone;
}

