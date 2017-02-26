

#include "BattleTanks.h"
#include "MotionControllerComponent.h"
#include "WidgetInteractionComponent.h"
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

	LeftHandMesh->SetupAttachment(LeftHandController);
	RightHandMesh->SetupAttachment(RightHandController);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'")); // Finds cube static mesh and sets it to CubeVisualAsset

	if (CubeVisualAsset.Succeeded())
	{
		LeftHandMesh->SetStaticMesh(CubeVisualAsset.Object);
		LeftHandMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));

		RightHandMesh->SetStaticMesh(CubeVisualAsset.Object);
		RightHandMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Cube asset not found."));
	}

	// Setup WidgetInteraction Componet for MainMenu
	WidgetInteraction = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("MenuInteraction"));
	WidgetInteraction->SetupAttachment(RightHandMesh);
	WidgetInteraction->RelativeLocation = FVector(50.0f, 0, 50.0f); // Set trace to the center of the face that is away from the player
	WidgetInteraction->bShowDebug = true;
	
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

}

