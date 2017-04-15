

#include "BattleTanks.h"
#include "MotionControllerComponent.h"
#include "WidgetInteractionComponent.h"
#include "TankGameInstance.h"
#include "SoundManager.h"
#include "MainMenuCharacter.h"


// Sets default values
AMainMenuCharacter::AMainMenuCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a dummy root component (location, rotation, scale, collision primitive) for the sole purpose of attaching components to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Capsule settings (capsule is used for basic collision)
	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	CollisionCapsule->SetCapsuleHalfHeight(96.0f);
	CollisionCapsule->SetCapsuleRadius(16.0f);
	CollisionCapsule->SetupAttachment(RootComponent);
	
	// Camera settings
	HMDCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("HeadMountedDisplayCamera"));
	HMDCamera->SetRelativeLocation(FVector(0.0f, 0.0f, -110.0f));
	HMDCamera->SetupAttachment(RootComponent);

	// Scene settings (scene is used for location(?))
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Scene->SetupAttachment(RootComponent);

	// Controller Settings
	LeftHandController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Left Hand Controller"));
	LeftHandController->Hand = EControllerHand::Left;
	LeftHandController->SetupAttachment(RootComponent);

	RightHandController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Right Hand Controller"));
	RightHandController->Hand = EControllerHand::Right;
	RightHandController->SetupAttachment(RootComponent);

	// Meshes for controllers
	LeftHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Hand Mesh"));
	RightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Hand Mesh"));

	RightHandMesh->RelativeScale3D = FVector(1.0f, -1.0f, 1.0f); // Mirrors mesh about Y-Axis to create a right handed controller since we are only given a left handed controller.

	LeftHandMesh->SetupAttachment(LeftHandController);
	RightHandMesh->SetupAttachment(RightHandController);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TouchControllerAsset(TEXT("StaticMesh'/Engine/VREditor/Devices/Oculus/OculusControllerMesh'")); // Finds cube static mesh and sets it to TouchControllerAsset
	
	static ConstructorHelpers::FObjectFinder<USoundWave> MainMenuSelect(TEXT("SoundWave'/Game/Sounds/MainMenuSelect.MainMenuSelect'"));
	MainMenuSelectSound = MainMenuSelect.Object;

	if (TouchControllerAsset.Succeeded())
	{
		LeftHandMesh->SetStaticMesh(TouchControllerAsset.Object);
		RightHandMesh->SetStaticMesh(TouchControllerAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Asset not found."));
	}

	if (!MainMenuSelect.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Sound not found."));
	}

	// Setup WidgetInteraction Componet for MainMenu
	WidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("MenuInteraction"));
	WidgetInteraction->SetupAttachment(RightHandMesh);
	WidgetInteraction->RelativeLocation = FVector(4.0f, 0.0f, 0.0f); // Set trace to the center of the face that is away from the player
	WidgetInteraction->bShowDebug = true;
	WidgetInteraction->InteractionDistance = 5000.0f;
	
}

// Called when the game starts or when spawned
void AMainMenuCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainMenuCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AMainMenuCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Menu Interact", IE_Pressed, this, &AMainMenuCharacter::InteractWithMenu);

}

void AMainMenuCharacter::InteractWithMenu()
{
	if (WidgetInteraction->IsOverFocusableWidget())
	{
		WidgetInteraction->PressPointerKey(EKeys::LeftMouseButton); // Simulates a mouse click on the menu
		UTankGameInstance* GameInstance = Cast<UTankGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			USoundManager* SoundManager = GameInstance->GetSoundManager();
			SoundManager->PlaySound("MainMenuSelect", this, 0.5f, 1.0f, 0.0f, nullptr);
		}
		//UGameplayStatics::PlaySound2D(this, MainMenuSelectSound, 0.5f, 1.0f, 0.0f, nullptr);
	}

}
