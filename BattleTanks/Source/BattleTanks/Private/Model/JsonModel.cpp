

#include "BattleTanks.h"
#include "TankGameInstance.h"
#include "Model/ModelManager.h"
#include "JsonModel.h"


void UJsonModel::LoadFromFile(FString FileName)
{
	FString JsonString;

	if (FFileHelper::LoadFileToString(JsonString, *FileName)) // Attempt to json from file
	{
		TSharedRef< TJsonReader<TCHAR> > Reader = TJsonReaderFactory<TCHAR>::Create(JsonString);
		TSharedPtr<FJsonObject> JsonObjectPtr; // The object the json creates

		if (FJsonSerializer::Deserialize(Reader, JsonObjectPtr)) // Attempt to parse json
		{

			if (JsonObjectPtr->HasField(FString("parent"))) // If json has parent set parent to that value
			{
				Parent = JsonObjectPtr->GetStringField(FString("parent"));
			}

			if (JsonObjectPtr->HasField(FString("materials"))) // If json has a materials
			{
				TArray<TSharedPtr<FJsonValue>> MaterialArray = JsonObjectPtr->GetArrayField(FString("materials")); // Get materials as an array
				for (auto MaterialValue : MaterialArray)
				{
					TSharedPtr<FJsonObject> MaterialObject = MaterialValue->AsObject();
					if (MaterialObject->HasField(FString("name")) && MaterialObject->HasField(FString("path"))) // Check and see if json has required values for the material
					{
						auto MaterialName = MaterialObject->GetStringField(FString("name"));
						auto MaterialPath = MaterialObject->GetStringField(FString("path"));

						Materials.Add(MaterialName, MaterialPath); // Add material to map
					}
				}

			}

			if (JsonObjectPtr->HasField(FString("meshes"))) // If json has a meshes
			{
				TArray<TSharedPtr<FJsonValue>> MeshArray = JsonObjectPtr->GetArrayField(FString("meshes")); // Get meshes as an array
				for (auto MeshValue : MeshArray)
				{
					TSharedPtr<FJsonObject> MeshObject = MeshValue->AsObject();
					if (MeshObject->HasField(FString("name")) && MeshObject->HasField(FString("path"))) // Check and see if json has required values for the mesh
					{
						auto MeshName = MeshObject->GetStringField(FString("name"));
						auto MeshPath = MeshObject->GetStringField(FString("path"));

						Meshes.Add(MeshName, MeshPath); // Add mesh to map
					}
				}

			}
			if (JsonObjectPtr->HasField(FString("components"))) // If json has a components
			{
				TArray<TSharedPtr<FJsonValue>> ComponentArray = JsonObjectPtr->GetArrayField(FString("components"));  // Get components as an array
				for (auto MeshValue : ComponentArray)
				{
					TSharedPtr<FJsonObject> ComponentObject = MeshValue->AsObject();
					UJsonComponent* Component = NewObject<UJsonComponent>();

					if (ComponentObject->HasField(FString("parent"))) // Set component parent if value is present
					{
						Component->Parent = ComponentObject->GetStringField(FString("parent"));
					}

					Component->Name = ComponentObject->GetStringField(FString("name")); // Set component name, it is required!

					if (ComponentObject->HasField(FString("path"))) // Set component path to mesh if value is present
					{
						Component->Path = ComponentObject->GetStringField(FString("path"));
					}

					if (ComponentObject->HasField(FString("materials"))) // Handle materials if present
					{
						for (auto MaterialValue : ComponentObject->GetArrayField(FString("materials")))
						{
							auto MaterialObject = MaterialValue->AsObject();
							auto MaterialIndex = MaterialObject->GetIntegerField(FString("index")); // Get Index, if material is defined this is required
							auto MaterialPath = MaterialObject->GetStringField(FString("path")); // Get material path, if material is defined this is required

							Component->Materials.Add(MaterialIndex, MaterialPath);
						}
					}

					if (ComponentObject->HasField(FString("scale"))) // Get scale, must be a 3 value array ( X, Y, Z )
					{
						FVector ScaleToSet = FVector(0);
						auto ScaleValues = ComponentObject->GetArrayField(FString("scale"));
						ScaleToSet.X = ScaleValues[0]->AsNumber();
						ScaleToSet.Y = ScaleValues[1]->AsNumber();
						ScaleToSet.Z = ScaleValues[2]->AsNumber();

						Component->Scale = ScaleToSet;
					}

					if (ComponentObject->HasField(FString("rotation"))) // Get rotation, must be a 3 value array ( X, Y, Z )
					{
						FRotator RotationToSet = FRotator(0);
						auto ScaleValues = ComponentObject->GetArrayField(FString("rotation"));
						RotationToSet.Pitch = ScaleValues[0]->AsNumber();
						RotationToSet.Yaw = ScaleValues[1]->AsNumber();
						RotationToSet.Roll = ScaleValues[2]->AsNumber();

						Component->Rotation = RotationToSet;
					}

					if (ComponentObject->HasField(FString("location"))) // Get location, must be a 3 value array ( X, Y, Z )
					{
						FVector LocationToSet = FVector(0);
						auto LocationValues = ComponentObject->GetArrayField(FString("location"));
						LocationToSet.X = LocationValues[0]->AsNumber();
						LocationToSet.Y = LocationValues[1]->AsNumber();
						LocationToSet.Z = LocationValues[2]->AsNumber();

						Component->Location = LocationToSet;
					}

					if (ComponentObject->HasField(FString("parentComponent"))) // If component as a parent component to attach to, set it
					{
						Component->ParentComponent = ComponentObject->GetStringField(FString("parentComponent"));

						if (ComponentObject->HasField(FString("parentSocket"))) // Only read if the parent component is present
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

void UJsonModel::PreloadAssets(TSet<FString> &MeshesToLoad, TSet<FString> &MaterialToLoad)
{

	TArray<FString> ObjectsToPreLoad; // Used to get all values out of the maps below
	
	Meshes.GenerateValueArray(ObjectsToPreLoad);
	for (auto Mesh : ObjectsToPreLoad) // Add meshes to the mesh set
	{
		MeshesToLoad.Add(Mesh);
	}

	Materials.GenerateValueArray(ObjectsToPreLoad);
	for (auto Material : ObjectsToPreLoad) // Add materials to the mesh set
	{
		MaterialToLoad.Add(Material);
	}


	TArray<UJsonComponent*> ComponentsToLoad; // Used to get components out of component map

	Components.GenerateValueArray(ComponentsToLoad);

	for (UJsonComponent* Component : ComponentsToLoad) // Get all meshes and materials from components as well
	{
		FString Mesh = Component->Path;

		if (!Mesh.StartsWith(FString("$")) && !Mesh.IsEmpty()) // Check and make sure mesh is not an identifier before adding
		{
			MeshesToLoad.Add(Mesh);
		}

		Component->Materials.GenerateValueArray(ObjectsToPreLoad);
		for (auto Material : ObjectsToPreLoad)
		{
			if (!Material.StartsWith(FString("$"))) // Check and make sure material is not an identifier before adding
			{
				MaterialToLoad.Add(Material);
			}
		}
	}
}


TMap<FString, USceneComponent*> UJsonModel::AttachToActor(AActor* Actor)
{
	TMap<FString, USceneComponent*> AllComponents; // All avaliable components on actor

	for(auto Component : Actor->GetComponents()) // Add pre-existing scene components to map above
	{
		USceneComponent* SceneComponent = Cast<USceneComponent>(Component);
		if(SceneComponent)
			AllComponents.Add(SceneComponent->GetName(), SceneComponent);
	}

	TMap<FString, USceneComponent*> AddedComponents; // All components created from this model returned by method
	TArray<UJsonComponent*> ComponentsToAdd; // All components to make

	UJsonModel* CompositeModel = BuildCompositeModel(Cast<UTankGameInstance>(Actor->GetWorld()->GetGameInstance())); // get composite model for this model

	CompositeModel->Components.GenerateValueArray(ComponentsToAdd); // Get components to create

	bool createdComponent = true; // Make sure a component is made every loop

	while (ComponentsToAdd.Num() > 0) // Continue to make components until there are no more
	{
		if (!createdComponent) // If a component was not made during last loop warn user and exit
		{
			UE_LOG(LogTemp, Warning, TEXT("Possible infinite loop for model: %s\n\tCheck your json file! Exiting loop for safety"), *Name)
			break;
		}
		createdComponent = false;


		TArray<int32> ToRemove; // Store indexes that need to be removed at end of loop
		for (auto It = ComponentsToAdd.CreateIterator(); It; ++It) // Iterate through all components still needed to be created
		{
			auto JsonComponent = *It; 
			JsonComponent = BuildCompsiteComponent(CompositeModel, JsonComponent); // Build compsite component 
			if (JsonComponent->ParentComponent.IsEmpty() || AllComponents.Contains(JsonComponent->ParentComponent)) // Check the the component that this component attaches to exists
			{
				USceneComponent* ComponentToAttachTo = Actor->GetRootComponent(); // Default to root component 
				if (!JsonComponent->ParentComponent.IsEmpty()) // Set if there is a component to attach to 
				{
					ComponentToAttachTo = AllComponents[JsonComponent->ParentComponent];
				}

				FName SocketToAttachTo = NAME_None; // Default to no socket 
				if (!JsonComponent->ParentSocket.IsEmpty()) // Set if there is a socket to attach to 
				{
					SocketToAttachTo = FName(*JsonComponent->ParentSocket);
				}

				UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(Actor, FName(*JsonComponent->Name)); // Create UStaticMeshComponent
				Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				if (Mesh) // register component if created if not continue loop
				{
					Mesh->RegisterComponent();
					Mesh->AttachToComponent(ComponentToAttachTo, FAttachmentTransformRules::KeepRelativeTransform, SocketToAttachTo);
				}
				else
				{
					continue; // Shouldn't happen?
				}

				FString ItemMeshPath = JsonComponent->Path; // Parse mesh
				if (ItemMeshPath.StartsWith(FString("$"))) // If mesh is an identifier
				{
					FString MeshID = FString(ItemMeshPath); // Remove the first character
					MeshID.RemoveFromStart(FString("$"));
					if (CompositeModel->Meshes.Contains(MeshID)) // Check that identifier has a mesh registered to it then set
					{
						ItemMeshPath = CompositeModel->Meshes[MeshID];
					}
					else 
					{
						// TODO Decide Default
					}
				}

				auto ItemMesh = GetStaticMesh(FName(*ItemMeshPath)); // Get Mesh

				if (ItemMesh) // If successfull set mesh, scale, location, rotation, and materials
				{
					Mesh->SetStaticMesh(ItemMesh);
					Mesh->SetWorldScale3D(JsonComponent->Scale);
					Mesh->SetRelativeLocationAndRotation(JsonComponent->Location, JsonComponent->Rotation);
					for (auto& MaterialEntry : JsonComponent->Materials) 
					{
						FString MaterialPath = MaterialEntry.Value; // Parse material
						if (MaterialPath.StartsWith(FString("$"))) // If material is an identifier
						{
							FString MaterialID = FString(MaterialPath); // Remove the first character
							MaterialID.RemoveFromStart(FString("$"));
							if (CompositeModel->Materials.Contains(MaterialID)) // Check that identifier has a material registered to it then set
							{
								MaterialPath = CompositeModel->Materials[MaterialID];
							}
							else
							{
								// TODO Decide Default
							}

						}

						auto Material = GetMaterial(FName(*MaterialPath)); // Get material

						if (Material) // If successful set material with proper index
						{
							Mesh->SetMaterial(MaterialEntry.Key, Material);
						}
					}
					
				}
				else
				{
					//UE_LOG(LogTemp, Warning, TEXT("Unable to find cube?"));
				}

				AllComponents.Add(JsonComponent->Name, Mesh); // Add componet to current component map
				AddedComponents.Add(JsonComponent->Name, Mesh); // Add component to created component map
				ToRemove.Add(It.GetIndex()); // Add index to remove after iteration is over
				createdComponent = true; // Mark as component created during this loop
			}
			else
			{
				// Do Nothing
			}
			for (auto Remove : ToRemove) // Remove created components to avoid recreating them
			{
				ComponentsToAdd.RemoveAt(Remove);
			}
		}
	}

	// Return all components added from model
	return AddedComponents;
}



UJsonModel* UJsonModel::BuildCompositeModel(UTankGameInstance* GameInstance)
{
	if (Parent.IsEmpty()) // If no parent then clone
		return Clone();

	if (GameInstance)
	{
		UModelManager* ModelManager = GameInstance->GetModelManager();  // Get model manager to retreive parent model
		UJsonModel* ParentModel = ModelManager->GetModel(Parent); // Get parent model

		// TODO check if parent is empty? throw error?

		ParentModel = ParentModel->BuildCompositeModel(GameInstance); // Create composite of parent model

		// Update composite model with this model's information
		ParentModel->Name = Name; // Set parent just in case
		ParentModel->Parent = Parent; // Set name just in case
		ParentModel->Materials.Append(Materials); // Append to material map as it overrides values
		ParentModel->Meshes.Append(Meshes); // Append to mesh map as it overrides values
		ParentModel->Components.Append(Components); // Append to component map as it overrides values

		// Return composite
		return ParentModel;
	}

	return NewObject<UJsonModel>(); // Should NEVER Reach
}

UJsonComponent* UJsonModel::BuildCompsiteComponent(UJsonModel* Model, UJsonComponent* JsonComponent)
{
	if (JsonComponent->Parent.IsEmpty()) // If no parent then clone
		return JsonComponent->Clone();

	UJsonComponent* ParentComponent = Model->Components[JsonComponent->Parent]; // Get parent component

	UJsonComponent* CompsiteComponent = BuildCompsiteComponent(Model, ParentComponent);  // Create composite of parent component

	// Update composite component with this component's information
	CompsiteComponent->Parent = JsonComponent->Parent; // Set parent just in case
	CompsiteComponent->Name = JsonComponent->Name; // Set proper name of component don't want duplicate component names

	if(!JsonComponent->Path.IsEmpty()) // Only set if exists
		CompsiteComponent->Path = JsonComponent->Path;

	CompsiteComponent->Materials.Append(JsonComponent->Materials); // Append to material map as it overrides values

	if(CompsiteComponent->Scale != JsonComponent->Scale) // Only set if not equal
		CompsiteComponent->Scale = JsonComponent->Scale;

	if (CompsiteComponent->Rotation != JsonComponent->Rotation) // Only set if not equal
		CompsiteComponent->Rotation = JsonComponent->Rotation;
	
	if (CompsiteComponent->Location != JsonComponent->Location) // Only set if not equal
		CompsiteComponent->Location = JsonComponent->Location;

	if (!JsonComponent->ParentComponent.IsEmpty()) // Only set if exists
	{
		CompsiteComponent->ParentComponent = JsonComponent->ParentComponent;
		CompsiteComponent->ParentSocket = FString();

		if (!JsonComponent->ParentSocket.IsEmpty()) // Only set if exists and parent component exists
			CompsiteComponent->ParentSocket = JsonComponent->ParentSocket;
	}
	return CompsiteComponent;

}

UJsonModel* UJsonModel::Clone()
{
	UJsonModel* Clone = NewObject<UJsonModel>(); // Create new model

	// Set information to same as this. Strings are not copied as they should not be changed just set
	Clone->Name = Name;
	Clone->Parent = Parent;
	Clone->Materials = TMap<FString, FString>(Materials); // This creates a copy so that if one map is changed the other doesn't
	Clone->Meshes = TMap<FString, FString>(Meshes);
	Clone->Components= TMap<FString, UJsonComponent*>(Components);

	return Clone;
}

