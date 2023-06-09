// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnim.generated.h"

/**
 * 
 */
UCLASS()
class UCharacterAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	// ���� �ִϸ��̼� ��Ÿ�� ��� �Լ�
	void PlayAttackAnim();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=PlayerAnim)
	float speed = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	float direction = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	bool isInAir = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	bool damaged = false;

	// ����� ���� �ִϸ��̼� ��Ÿ��
	UPROPERTY(EditDefaultsOnly, Category=PlayerAnim)
	class UAnimMontage* attackAnimMontage;

	// ���� �ִϸ��̼� ������ �̺�Ʈ �Լ�
	UFUNCTION(BlueprintCallable, Category = FSMEvent)
	void OnEndDamageAnimation();

	// �ǰ� �ִϸ��̼� ��� �̺�Ʈ �Լ�
	UFUNCTION(BlueprintImplementableEvent, Category = FSMEvent)
	void PlayDamageAnim(FName sectionName);
};
