// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Enemy.h"
#include "TPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATPSCharacter::StaticClass());
	playerTarget = Cast<ATPSCharacter>(actor);
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	timer += DeltaTime;
	if (timer >= spawnTime)
	{
		SpawnEnemy();
		timer = 0.0f;
		spawnTime = UKismetMathLibrary::RandomFloatInRange(minSpawnTime, maxSpawnTime);
	}
}

void AEnemySpawner::SpawnEnemy()
{
	FVector spawnLocation = FVector::ZeroVector;
	spawnLocation = UKismetMathLibrary::RandomUnitVector()* UKismetMathLibrary::RandomFloatInRange(0.0f, spawnRange);
	spawnLocation += GetActorLocation();
	spawnLocation.Z = zLocation;
	FTransform spawnTransform = UKismetMathLibrary::MakeTransform(spawnLocation, FRotator::ZeroRotator);

	/*UObject* ClassPackage = ANY_PACKAGE;
	UObject* ObjectToSpawn;
	ObjectToSpawn = FindObject<UObject>(ClassPackage, TEXT("/Script/Engine.Blueprint'/Game/TPSContent/Blueprints/BP_RealEnemySpawner.BP_RealEnemySpawner'"));
	UClass* ClassToSpawn = ObjectToSpawn->StaticClass();
	AActor* actor = GetWorld()->SpawnActor(ClassToSpawn->StaticClass(), &spawnTransform);
	AEnemy* enemy = Cast<AEnemy>(actor->GetClass());
	if (enemy != nullptr)
	{
		enemy->InitEnemy(playerTarget, 1.0f);
	}*/

	FName path = TEXT("/Script/Engine.Blueprint'/Game/TPSContent/Blueprints/BP_Enemy.BP_Enemy'");
	UBlueprint* ObjectToSpawn =
		Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, *path.ToString()));
	AActor* actor = GetWorld()->SpawnActor<AActor>(ObjectToSpawn->GeneratedClass, spawnTransform);
	AEnemy* enemy = Cast<AEnemy>(actor); // cast Actor to Pawn, return valid pawn.
	if (enemy != nullptr)
	{
		enemy->InitEnemy(playerTarget, 1.0f);
	}
}

