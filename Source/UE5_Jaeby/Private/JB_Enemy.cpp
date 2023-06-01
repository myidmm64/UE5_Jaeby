// Fill out your copyright notice in the Description page of Project Settings.


#include "JB_Enemy.h"

// Sets default values
AJB_Enemy::AJB_Enemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJB_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJB_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AJB_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

