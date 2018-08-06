// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemigo.h"
#include "MyAIController.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"


// Sets default values
AEnemigo::AEnemigo()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//Set the peripheral vision angle to 90 degrees
	PawnSensingComp->SetPeripheralVisionAngle(30.f);
	OnActorHit.AddDynamic(this, &AEnemigo::OnHit);
}

// Called when the game starts or when spawned
void AEnemigo::BeginPlay()
{
	Super::BeginPlay();
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemigo::OnSeePlayer);
	}
}

// Called every frame
void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemigo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemigo::OnSeePlayer(APawn* Pawn)
{
	AMyAIController* AIController = Cast<AMyAIController>(GetController());
	//Set the seen target on the blackboard
	if (AIController)
	{
		GLog->Log("Oh hello there");
		AIController->SetSeenTarget(Pawn);
	}
}

void AEnemigo::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{

	AMyAIController* AIController = Cast<AMyAIController>(GetController());
	//Set the seen target on the blackboard
	if (AIController)
	{

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Enemigo golpeado!"));
		UpdateLife();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Enemigo golpeado! %f"), Health));
		//SelfActor->Destroy();
	}
}

void AEnemigo::UpdateLife() {
	Health -= 25.f;
	if (Health <= 0) {
		Health = 0.0f;
		Destroy();
	}
}