// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE4_CPP_Demo_FCCGameMode.h"
#include "UE4_CPP_Demo_FCCCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE4_CPP_Demo_FCCGameMode::AUE4_CPP_Demo_FCCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
