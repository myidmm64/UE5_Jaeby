// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAnim.h"
#include "TPSCharacter.h"
#include <GameFramework/CharacterMovementComponent.h>

void UCharacterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// ���� �� ��� ����
	auto ownerPawn = TryGetPawnOwner();

	// �÷��̾�� ĳ����
	auto player = Cast<ATPSCharacter>(ownerPawn);

	if (player)
	{
		speed = player->speed;
		direction = player->direction;

		auto movement = player->GetCharacterMovement();
		if (movement)
			isInAir = movement->IsFalling();
	}
}

void UCharacterAnim::PlayAttackAnim()
{
	Montage_Play(attackAnimMontage);
}

void UCharacterAnim::OnEndDamageAnimation()
{
	damaged = false;
}
