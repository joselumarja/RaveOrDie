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
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	FVector CalcDirection();

	const float Velocity = 100.f;

	FVector AcumulatedDirection;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);
	

};
