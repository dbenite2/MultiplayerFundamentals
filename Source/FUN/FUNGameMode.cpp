// Copyright Epic Games, Inc. All Rights Reserved.

#include "FUNGameMode.h"
#include "FUNCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFUNGameMode::AFUNGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
