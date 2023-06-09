// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyFSM.h"
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class UEnemyAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// 상태 머신 정보 기억 변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=FSM)
	EEnemyState animState;

	// 공격 상태 재생할지 여부 판단 변수
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FSM)
	bool bAttackPlay = false;

	// 공격 애니메이션 끝나는 이벤트 함수
	UFUNCTION(BlueprintCallable, Category = FSMEvent)
	void OnEndAttackAnimation();

	// 피격 애니메이션 재생 이벤트 함수
	UFUNCTION(BlueprintImplementableEvent, Category=FSMEvent)
	void PlayDamageAnim(FName sectionName);
};
