// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPS_EandrushenkoGameMode.h"
#include "FPS_EandrushenkoHUD.h"
#include "FPS_EandrushenkoCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "MenuPlayerController.h"

AFPS_EandrushenkoGameMode::AFPS_EandrushenkoGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	PlayerControllerClass = AMenuPlayerController::StaticClass();
	HUDClass = AFPS_EandrushenkoHUD::StaticClass();
}
