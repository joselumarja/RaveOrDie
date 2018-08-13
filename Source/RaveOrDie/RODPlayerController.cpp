// Fill out your copyright notice in the Description page of Project Settings.

#include "RODPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Engine/World.h"

ARODPlayerController::ARODPlayerController()
{
	FVector AcumulatedDirection = FVector(0, 0, 0);

}

void ARODPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	APawn* const MyPawn = GetPawn();
	if (MyPawn) 
	{
		FVector LastDirection = CalcDirection();
		if (LastDirection.SizeSquared() > 0.f)
		{

			AcumulatedDirection += LastDirection*Velocity*DeltaTime;
			if (FVector::Dist(AcumulatedDirection, MyPawn->GetActorLocation()) > 120.f) 
			{
				SetNewMoveDestination(AcumulatedDirection);
				AcumulatedDirection.X = 0;
				AcumulatedDirection.Y = 0;
				AcumulatedDirection.Z = 0;
			}
		}
	}
	
	
	
}

void ARODPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAxis(MoveYBinding);
	InputComponent->BindAxis(MoveXBinding);

}

FVector ARODPlayerController::CalcDirection()
{
	const float YValue = GetInputAxisValue(MoveYBinding);
	const float XValue = GetInputAxisValue(MoveXBinding);

	const FVector MoveDirection = FVector(YValue, XValue, 0.f).GetClampedToMaxSize(1.f);
	
	return MoveDirection;
}

void ARODPlayerController::SetNewMoveDestination(const FVector DestLocation)
{

	UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();

	if (NavSys)
	{
		NavSys->SimpleMoveToLocation(this, DestLocation);
	}
}




