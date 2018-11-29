// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "VIrtPirates_181127GameMode.h"
#include "VIrtPirates_181127HUD.h"
#include "VIrtPirates_181127Character.h"
#include "UObject/ConstructorHelpers.h"

AVIrtPirates_181127GameMode::AVIrtPirates_181127GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AVIrtPirates_181127HUD::StaticClass();
}
