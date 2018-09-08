// Fill out your copyright notice in the Description page of Project Settings.

#include "RODPlayerController.h"
#include "RODCharacter.h"
#include "GameManager.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Engine/World.h"
#include "Engine.h"

ARODPlayerController::ARODPlayerController()
{
	a = 0.f;
}

void ARODPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MyPawn = Cast<ARODCharacter>(GetPawn());
}

void ARODPlayerController::MoveFordward(float Value)
{

	if ((MyPawn != NULL) && (Value != 0.f) && !MyPawn->IsInMeleeAttack())
	{
		const FVector Direction = FVector(1.f, 0.f, 0.f);
		MyPawn->AddMovementInput(Direction, Value);
	}
}

void ARODPlayerController::MoveRight(float Value)
{
	if ((MyPawn != NULL) && (Value != 0.f) && !MyPawn->IsInMeleeAttack())
	{
		const FVector Direction = FVector(0.f, 1.f, 0.f);

		MyPawn->AddMovementInput(Direction, Value);
	}
}

void ARODPlayerController::RotationX(float Value)
{
	a = Value;
}


void ARODPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis(MoveYBinding,this,&ARODPlayerController::MoveFordward);
	InputComponent->BindAxis(MoveXBinding,this,&ARODPlayerController::MoveRight);

	InputComponent->BindAxis(RotationXBinding, this, &ARODPlayerController::RotationX);

	InputComponent->BindAction(AttackBinding, IE_Pressed, this, &ARODPlayerController::Attack);
	InputComponent->BindAction(SwapWeaponBinding, IE_Pressed, this, &ARODPlayerController::SwapWeapon);


}

void ARODPlayerController::Attack()
{
	ARODCharacter* RODCharacter = Cast<ARODCharacter>(GetPawn());
	if (RODCharacter !=NULL)
	{
		RODCharacter->Attack();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Ataco"));
	}
}



void ARODPlayerController::SwapWeapon()
{
	ARODCharacter* RODCharacter = Cast<ARODCharacter>(GetPawn());
	if (RODCharacter != NULL)
	{
		RODCharacter->SwapWeapon();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Cambio de arma"));
	}
}




