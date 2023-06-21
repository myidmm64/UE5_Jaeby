// Fill out your copyright notice in the Description page of Project Settings.


#include "HealPack.h"
#include <TPSCharacter.h>

// Sets default values
AHealPack::AHealPack()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHealPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalRotation(FRotator(0.0f, 0.0f, DeltaTime * rotateSpeed));
}

// Called to bind functionality to input
void AHealPack::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHealPack::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*ATPSCharacter* player = Cast<ATPSCharacter>(OtherActor);
	if (player != nullptr)
	{
	}*/
}

