// Fill out your copyright notice in the Description page of Project Settings.

#include "GameManager.h"
#include "Enemigo.h"

#include "Runtime/Core/Public/Containers/Array.h"
#include "Engine.h"

TWeakObjectPtr<UGameManager> UGameManager::Manager = nullptr;

UGameManager::UGameManager() 
{

}

TWeakObjectPtr<UGameManager> UGameManager::GetManager()
{
	if (!Manager.IsValid())
	{
		Manager = NewObject<UGameManager>();
	}

	return Manager;
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

void UGameManager::ResetStatistics()
{

}

void UGameManager::GameOver()
{

}



