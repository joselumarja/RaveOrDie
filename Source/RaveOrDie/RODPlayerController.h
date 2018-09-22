// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RODPlayerController.generated.h"

class UGameManager;
class ARODCharacter;

UCLASS()
class RAVEORDIE_API ARODPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ARODPlayerController();

	void BeginPlay() override;

	UFUNCTION()
	FORCEINLINE float CalcRotation() const { return a*1.5; }

	const FName MoveYBinding=FName("MoveY");
	const FName MoveXBinding=FName("MoveX");
	const FName AttackBinding = FName("Attack");
	const FName SwapWeaponBinding = FName("SwapWeapon");
	const FName ReloadBinding = FName("Reload");
	const FName RotationXBinding = FName("RotationX");
	const FName RotationYBinding = FName("RotationY");

protected:

	// Begin PlayerController interface
	virtual void SetupInputComponent() override;

	void MoveFordward(float Value);

	void MoveRight(float Value);

	void RotationX(float Value);

	void Attack();

	void SwapWeapon();

	void Reload();

	float a;

	ARODCharacter* MyPawn;

};
