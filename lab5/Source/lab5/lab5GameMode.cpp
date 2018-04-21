// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "lab5.h"
#include "lab5GameMode.h"
#include "lab5PlayerController.h"
#include "lab5Character.h"

Alab5GameMode::Alab5GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = Alab5PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}