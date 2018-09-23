// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerBox1.h"
#include "Engine.h"
#include "GameManager.h"
#include "RODCharacter.h"
#include "RODGameStateBase.h"

void ATriggerBox1::BeginPlay()
{
	Super::BeginPlay();

	GameManager = Cast<ARODGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->GetGameManager();
	
}

ATriggerBox1::ATriggerBox1() 
{
	OnActorBeginOverlap.AddDynamic(this, &ATriggerBox1::OnOverlapBegin);

}



void ATriggerBox1::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor) {
	
	ARODCharacter* RODCharacter = Cast<ARODCharacter>(OtherActor);
	if (RODCharacter && NumberOfEnemies>0)
	{
		GameManager->SpawnEnemies(NumberOfEnemies, SpawnLocation, EnemiesRotation);
		MarkPendingKill();
	}
}





