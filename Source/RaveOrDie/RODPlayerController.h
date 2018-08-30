// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RODPlayerController.generated.h"

class UGameManager;

UCLASS()
class RAVEORDIE_API ARODPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ARODPlayerController();

	void BeginPlay() override;

	const FName MoveYBinding=FName("MoveY");
	const FName MoveXBinding=FName("MoveX");
	const FName AttackBinding = FName("Attack");
	const FName SwapWeaponBinding = FName("SwapWeapon");

protected:

	UPROPERTY()
	TWeakObjectPtr<UGameManager> Manager;

	// Begin PlayerController interface
	virtual void SetupInputComponent() override;

	void MoveFordward(float Value);

	void MoveRight(float Value);

	void Attack();

	void SwapWeapon();

};
