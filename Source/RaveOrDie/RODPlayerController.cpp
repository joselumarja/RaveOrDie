// Fill out your copyright notice in the Description page of Project Settings.

#include "RODPlayerController.h"
#include "RODCharacter.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Engine/World.h"
#include "Engine.h"

ARODPlayerController::ARODPlayerController()
{
	bCanDistanceAttak = true;
	bCanMeleeAttak = true;
}

void ARODPlayerController::MoveFordward(float Value)
{
	APawn* const MyPawn = GetPawn();
	if ((MyPawn != NULL) && (Value != 0.f))
	{
		const FVector Direction = FVector(1.f, 0.f, 0.f);
		MyPawn->AddMovementInput(Direction, Value);
	}
}

void ARODPlayerController::MoveRight(float Value)
{
	APawn* const MyPawn = GetPawn();
	if ((MyPawn != NULL) && (Value != 0.f))
	{
		const FVector Direction = FVector(0.f, 1.f, 0.f);

		MyPawn->AddMovementInput(Direction, Value);
	}
}

void ARODPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis(MoveYBinding,this,&ARODPlayerController::MoveFordward);
	InputComponent->BindAxis(MoveXBinding,this,&ARODPlayerController::MoveRight);

	InputComponent->BindAction(MeleeAttakName, IE_Pressed, this, &ARODPlayerController::MeleeAttak);
	InputComponent->BindAction(DistanceAttakName, IE_Pressed, this, &ARODPlayerController::DistanceAttak);

	InputComponent->BindAction(MeleeAttakName, IE_Released, this, &ARODPlayerController::FinishMeleeAttak);
	InputComponent->BindAction(DistanceAttakName, IE_Released, this, &ARODPlayerController::FinishDistanceAttak);
}

void ARODPlayerController::MeleeAttak()
{
	if (bCanMeleeAttak) 
	{
		bCanDistanceAttak = false;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Navajeo"));
		//hacer cosas
	}
}

void ARODPlayerController::FinishMeleeAttak()
{
	bCanDistanceAttak = true;
}

void ARODPlayerController::DistanceAttak()
{
	if (bCanDistanceAttak)
	{
		bCanMeleeAttak = false;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Disparo"));
		//hacer cosas
	}
}

void ARODPlayerController::FinishDistanceAttak()
{
	bCanMeleeAttak = true;
}



