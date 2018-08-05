// Fill out your copyright notice in the Description page of Project Settings.

#include "RaveOrDieGameModeBase.h"
#include "RODPlayerController.h"
#include "RODCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARaveOrDieGameModeBase::ARaveOrDieGameModeBase()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARODPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/RODCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


