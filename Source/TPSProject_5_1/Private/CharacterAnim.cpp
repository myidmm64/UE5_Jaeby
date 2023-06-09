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
		FVector velocity = player->GetVelocity();
		FVector forward = player->GetActorForwardVector();
		speed = FVector::DotProduct(forward, velocity);

		FVector right = player->GetActorRightVector();
		direction = FVector::DotProduct(right, velocity);

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
