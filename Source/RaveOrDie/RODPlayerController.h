// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RODPlayerController.generated.h"

UCLASS()
class RAVEORDIE_API ARODPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ARODPlayerController();

	const FName MoveYBinding=FName("MoveY");
	const FName MoveXBinding=FName("MoveX");

protected:

	// Begin PlayerController interface
	virtual void SetupInputComponent() override;

	void MoveFordward(float Value);

	void MoveRight(float Value);
};
