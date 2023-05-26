// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "JB_PlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class UJB_PlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
public:
	// �� ������ ���ŵǴ� �Լ�
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerAnim)
	bool moving = false;

};
