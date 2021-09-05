// Copyright Epic Games, Inc. All Rights Reserved.

#include "AysncRestExampleGameMode.h"
#include "AysncRestExampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAysncRestExampleGameMode::AAysncRestExampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
