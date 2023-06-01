// Fill out your copyright notice in the Description page of Project Settings.


#include "JB_Character.h"
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <EnhancedInputComponent.h>
#include <Kismet/GameplayStatics.h>
#include <JB_Enemy.h>

// Sets default values
AJB_Character::AJB_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJB_Character::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AJB_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJB_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(moveFowardAction, ETriggerEvent::Triggered, this, &AJB_Character::ForwardAction);
		EnhancedInputComponent->BindAction(moveRightAction, ETriggerEvent::Triggered, this, &AJB_Character::RightAction);
	}
}

void AJB_Character::ForwardAction(const FInputActionValue& Value)
{
	float amount = moveAmount * Value.Get<float>();
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * amount);
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, GetActorLocation() + GetActorForwardVector() * amount);
}

void AJB_Character::RightAction(const FInputActionValue& Value)
{
	float amount = moveAmount * Value.Get<float>();
	SetActorLocation(GetActorLocation() + GetActorRightVector() * amount);
	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller,);
}

