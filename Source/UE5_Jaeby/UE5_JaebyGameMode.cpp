// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5_JaebyGameMode.h"
#include "UE5_JaebyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE5_JaebyGameMode::AUE5_JaebyGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
