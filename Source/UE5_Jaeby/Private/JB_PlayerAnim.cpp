// Fill out your copyright notice in the Description page of Project Settings.


#include "JB_PlayerAnim.h"
#include <UE5_Jaeby/UE5_JaebyCharacter.h>

void UJB_PlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds); 
	auto ownerPawn = TryGetPawnOwner();
	auto player = Cast<AUE5_JaebyCharacter>(ownerPawn);
	if (player)
	{
		moving = player->GetIsMoving();
	}
}
