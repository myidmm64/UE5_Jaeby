// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemy();
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	float timer = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	float spawnTime = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	float minSpawnTime = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	float maxSpawnTime = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	float zLocation = 90.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	float spawnRange = 1000.0f;

	class ATPSCharacter* playerTarget;
};
