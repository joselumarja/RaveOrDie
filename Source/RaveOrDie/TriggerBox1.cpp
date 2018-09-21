// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerBox1.h"
#include "Engine.h"
#include "GameManager.h"
#include "RODGameStateBase.h"

void ATriggerBox1::BeginPlay()
{
	Super::BeginPlay();

	GameManager = Cast<ARODGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->GetGameManager();
	
}

ATriggerBox1::ATriggerBox1() {

	OnActorBeginOverlap.AddDynamic(this, &ATriggerBox1::OnOverlapBegin);

	OnActorEndOverlap.AddDynamic(this, &ATriggerBox1::OnOverlapEnd);


}



void ATriggerBox1::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Dentro caja"));
	
	
	int NumberEnemies = FMath::RandRange(1, 10);

	//Spawn enemigos
	//GameManager->SpawnEnemies(NumberEnemies, SpawnPosition);
	
}


void ATriggerBox1::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("Fuera caja"));

	//destruimos la caja para no lanzarla mas
	Destroy();
}



