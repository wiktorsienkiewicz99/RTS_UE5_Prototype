// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

/**
 * Constructor for the AControllerPawn class. Initializes default components and settings for the pawn.
 *
 * This constructor sets up the following components and settings:
 * - Enables ticking for every frame.
 * - Creates and attaches a capsule component as the root.
 * - Creates and attaches a camera component to a spring arm, with specific rotation and arm length.
 * - Configures the camera to use a perspective projection mode.
 * - Adds a floating pawn movement component for movement functionality.
 * - Attaches input action for movement from assets, if found.
 * - Sets the capsule component visibility for in-game.
 *
 * @return AControllerPawn instance with initialized components and properties to function in the game environment.
 */
AControllerPawn::AControllerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create capsule component
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent = CapsuleComponent;

	//Create a Camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	//Create Spring Arm
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));

	//Attach components
	SpringArmComponent->SetupAttachment(RootComponent);

	//Attach camera to spring arm
	CameraComponent->SetupAttachment(SpringArmComponent);

	//Spring arm settings
	SpringArmComponent->SetRelativeRotation(FRotator(-50, 0, 0));
	SpringArmComponent->TargetArmLength = 900;

	//Change perspective
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);

	//Create a floating movement
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	//Set capsule visibility in game
	CapsuleComponent->SetHiddenInGame(false);
	
	//attach IA Move
	ConstructorHelpers::FObjectFinder<UInputAction> MoveActionAsset(TEXT("/RTSUtills/Blueprints/Input/InputActions/IA_Move.IA_Move"));
	if (MoveActionAsset.Succeeded())
	{
		MoveAction = MoveActionAsset.Object;
	}
}

// Called when the game starts or when spawned
void AControllerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

/**
 * Handles movement input for the pawn.
 *
 * This method is bound to a movement input action and facilitates the pawn's movement based on the directional input.
 * It calculates the forward and right movement vectors relative to the controller's current rotation.
 * Movement is then applied accordingly along these vectors.
 *
 * @param Value The input value containing directional movement data as a 2D vector (X and Y axes).
 */
void AControllerPawn::Move(const FInputActionValue& Value)
{
	const FVector2D MovementInput = Value.Get<FVector2D>();
	if (Controller)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		AddMovementInput(Forward, MovementInput.Y, true);
		AddMovementInput(Right, MovementInput.X, true);
	}
}

// Called every frame
void AControllerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
 * Binds input actions to the player-controlled pawn to handle player input.
 *
 * This method sets up input bindings for the pawn, allowing it to respond to player input.
 * Specifically, this method binds the move action input to the Move function, enabling movement functionality.
 *
 * @param PlayerInputComponent The input component where player input bindings are added.
 */
void AControllerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//bind move function to move input action
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AControllerPawn::Move);
	}


}

