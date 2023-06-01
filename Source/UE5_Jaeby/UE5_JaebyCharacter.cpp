// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_JaebyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


//////////////////////////////////////////////////////////////////////////
// AUE5_JaebyCharacter

AUE5_JaebyCharacter::AUE5_JaebyCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AUE5_JaebyCharacter::Tick(float DeltaTime)
{
	Move(DeltaTime);
}

void AUE5_JaebyCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AUE5_JaebyCharacter::Move(float deltaTime)
{
	if (isMoving == false)
		return;
	if (timer >= 1.0f)
	{
		isMoving = false;
		timer = 0.0f;
		SetActorLocation(startVector + endVector);
		return;
	}

	SetActorLocation(startVector + endVector * timer);
	timer += deltaTime * (1 / moveTime);
}

bool AUE5_JaebyCharacter::GetIsMoving()
{
	return isMoving;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AUE5_JaebyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUE5_JaebyCharacter::Move);
	}

}

void AUE5_JaebyCharacter::Move(const FInputActionValue& Value)
{
	if (isMoving)
		return;

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	FVector amount = GetActorForwardVector() * MovementVector.Y + GetActorRightVector() * MovementVector.X;
	amount.Normalize();
	amount = amount * moveAmount;
	startVector = GetActorLocation();
	endVector = amount;
	isMoving = true;
	timer = 0.0f;
}




