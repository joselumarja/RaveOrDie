// Fill out your copyright notice in the Description page of Project Settings.

#include "BTMoveToPlayer.h"
#include "RODCharacter.h"
#include "MyAIController.h"
#include "RangedEnemigo.h"
#include "Boss.h"
#include "MeleeEnemigo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemigo.h"

/* THIS NODE EVALUATES THE DISTANCE FROM THE ENEMY TO THE PLAYER */

EBTNodeResult::Type UBTMoveToPlayer::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	
	
		AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
		
		if (AICon)
		{

			UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
			AEnemigo* Enemigo = Cast<AEnemigo>(BlackboardComp->GetValueAsObject("SelfActor"));

			float Distance=Enemigo->DistanceToPlayer();
			if (Distance < 800.0f){
				return EBTNodeResult::Succeeded;
			}
			//At this point, the task has been successfully completed
		
		}

	
	return EBTNodeResult::Failed;
	
}