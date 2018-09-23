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

	if ((MyPawn != NULL) && !MyPawn->GetIsDead() && (Value != 0.f) && !MyPawn->IsInMeleeAttack())
	{
		const FVector Direction = FVector(1.f, 0.f, 0.f);
		MyPawn->AddMovementInput(Direction, Value);
	}
}

void ARODPlayerController::MoveRight(float Value)
{

	if ((MyPawn != NULL) && !MyPawn->GetIsDead() && (Value != 0.f) && !MyPawn->IsInMeleeAttack())
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
	InputComponent->BindAction(ReloadBinding, IE_Pressed, this, &ARODPlayerController::Reload);


}

void ARODPlayerController::Reload()
{
	if (MyPawn != NULL && !MyPawn->GetIsDead())
	{
		MyPawn->Reload();
	}
}

void ARODPlayerController::Attack()
{

	if (MyPawn != NULL && !MyPawn->GetIsDead())
	{
		MyPawn->Attack();
		
	}
}



void ARODPlayerController::SwapWeapon()
{

	if (MyPawn != NULL && !MyPawn->GetIsDead())
	{
		MyPawn->SwapWeapon();
		
	}
}




