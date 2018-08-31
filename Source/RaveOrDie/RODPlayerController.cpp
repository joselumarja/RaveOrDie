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

}

void ARODPlayerController::BeginPlay()
{

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

	InputComponent->BindAction(AttackBinding, IE_Pressed, this, &ARODPlayerController::Attack);
	InputComponent->BindAction(SwapWeaponBinding, IE_Pressed, this, &ARODPlayerController::SwapWeapon);

}

void ARODPlayerController::Attack()
{
	ARODCharacter* RODCharacter = Cast<ARODCharacter>(GetPawn());
	if (RODCharacter !=NULL && RODCharacter->GetCanAttack())
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




