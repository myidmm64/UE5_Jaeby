// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"


// 사용할 상태 정의
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEnemyFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// 대기상태
	void IdleState();
	// 이동상태
	void MoveState();
	// 공격상태
	void AttackState();
	// 피격상태
	void DamageState();
	// 죽음상태
	void DieState();

public:
	// 피격 이벤트 처리 함수
	void OnDamageProcess();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=FSM)
	EEnemyState mState = EEnemyState::Idle;

	// 대기 상태 관련 변수
	// 대기시간
	UPROPERTY(EditDefaultsOnly, Category=FSM)
	float idleDelayTime = 2.0f;

	// 이동 상태 관련 변수
	// 대상
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = FSM)
	class ATPSCharacter* target;
	float speedScale = 1.0f;

	// 소유 액터
	class AEnemy* me;

	// 공격 상태 관련 변수
	// 공격 범위
	UPROPERTY(EditAnywhere, Category=FSM)
	float attackRange = 150.0f;

	// 공격 대기 시간
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackDelayTime = 2.0f;

	// 피격 상태 관련 변수
	// 체력
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FSM)
	int hp = 3;

	// 피격 대기 시간
	UPROPERTY(EditAnywhere, Category=FSM)
	float damageDelayTime = 2.0f;

	// 죽음 상태 관련 변수
	// 아래로 내려가는 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FSM)
	float dieSpeed = 0.0f;

	// 경과시간
	float currentTime = 0.0f;

	// 사용 중인 애니메이션 블루프린트
	class UEnemyAnim* anim;
};
