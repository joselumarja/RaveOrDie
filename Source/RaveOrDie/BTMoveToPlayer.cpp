// Fill out your copyright notice in the Description page of Project Settings.

#include "BTMoveToPlayer.h"
#include "RODCharacter.h"
#include "MyAIController.h"
#include "RangedEnemigo.h"
#include "Enemigo.h"
#include "Boss.h"
#include "MeleeEnemigo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "RangedEnemigo.h"



EBTNodeResult::Type UBTMoveToPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	
		AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
		
		if (AICon)
		{

			UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();

			AEnemigo* Enemigo = Cast<AEnemigo>(BlackboardComp->GetValueAsObject("SelfActor"));

			float Distance = Enemigo->DistanceToPlayer();
			BlackboardComp->SetValueAsFloat("Distancia", Distance);
			Enemigo->MoveToPlayer();
		}

	
	return EBTNodeResult::Succeeded;
	
}