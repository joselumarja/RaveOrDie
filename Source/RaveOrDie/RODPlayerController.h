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

	const FName MoveYBinding=FName("MoveY");
	const FName MoveXBinding=FName("MoveX");
	const FName MeleeAttackBinding = FName("MeleeAttack");
	const FName DistanceAttackBinding = FName("DistanceAttack");

protected:

	TWeakObjectPtr<UGameManager> Manager;

	// Begin PlayerController interface
	virtual void SetupInputComponent() override;

	void MoveFordward(float Value);

	void MoveRight(float Value);

	void MeleeAttack();

	void DistanceAttack();

};
