// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyFSM.generated.h"


// ����� ���� ����
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
	// ������
	void IdleState();
	// �̵�����
	void MoveState();
	// ���ݻ���
	void AttackState();
	// �ǰݻ���
	void DamageState();
	// ��������
	void DieState();

public:
	// �ǰ� �̺�Ʈ ó�� �Լ�
	void OnDamageProcess();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=FSM)
	EEnemyState mState = EEnemyState::Idle;

	// ��� ���� ���� ����
	// ���ð�
	UPROPERTY(EditDefaultsOnly, Category=FSM)
	float idleDelayTime = 2.0f;

	// �̵� ���� ���� ����
	// ���
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = FSM)
	class ATPSCharacter* target;

	// ���� ����
	class AEnemy* me;

	// ���� ���� ���� ����
	// ���� ����
	UPROPERTY(EditAnywhere, Category=FSM)
	float attackRange = 150.0f;

	// ���� ��� �ð�
	UPROPERTY(EditAnywhere, Category = FSM)
	float attackDelayTime = 2.0f;

	// �ǰ� ���� ���� ����
	// ü��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=FSM)
	int hp = 3;

	// �ǰ� ��� �ð�
	UPROPERTY(EditAnywhere, Category=FSM)
	float damageDelayTime = 2.0f;

	// ���� ���� ���� ����
	// �Ʒ��� �������� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=FSM)
	float dieSpeed = 0.0f;

	// ����ð�
	float currentTime = 0.0f;

	// ��� ���� �ִϸ��̼� �������Ʈ
	class UEnemyAnim* anim;
};
