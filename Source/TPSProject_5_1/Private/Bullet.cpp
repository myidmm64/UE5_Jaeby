// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// �浹ü ���̱�
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollsionComp"));
	if (collisionComp)
	{
		collisionComp->SetCollisionProfileName(TEXT("BlockALL"));
		collisionComp->SetSphereRadius(13);
		RootComponent = collisionComp;
	}

	// ���� ������Ʈ
	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	if (bodyMeshComp)
	{
		bodyMeshComp->SetupAttachment(collisionComp);
		bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		bodyMeshComp->SetRelativeScale3D(FVector(0.25f));
	}

	// �߻�ü �̵� ������Ʈ
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	if (movementComp)
	{
		// �߻�ü ������Ʈ�� ���Ž�ų ������Ʈ ����
		movementComp->SetUpdatedComponent(collisionComp);

		movementComp->InitialSpeed = 5000;
		movementComp->MaxSpeed = 5000;
		movementComp->bShouldBounce = true;
		movementComp->Bounciness = 0.3f;
	}

	// ���� �ð� �ֱ�
	// InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle deathTimer;
	GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ABullet::Die, 2.0f, false);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::Die()
{
	Destroy();
}

