// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Enemigo.h"
#include "Engine.h"

UGameManager::UGameManager()
{

}

void UGameManager::InitializeGameManager()
{
	UWorld* World = GetWorld();

	if (World != NULL)
	{
		for (TActorIterator<AEnemigo>ActorItr(World); ActorItr; ++ActorItr)
		{
			ActorItr->AddManager(this);
		}
	}
}

void UGameManager::EnemyKilled()
{
	EnemiesKilled++;
}