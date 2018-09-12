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
	/*
	if (OwnerComp.GetAIOwner()->GetPawn()->IsA(AEnemigo::StaticClass())) {
		AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
		/*If the Controller is valid:
		1)Get the Blackboard Component and the Current Point of the bot
		2)Search for the next point, which will be different from the Current Point
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
	}

	else if (OwnerComp.GetAIOwner()->GetPawn()->IsA(AFinalBoss::StaticClass())) {
		ABossAIController* BossAICon = Cast<ABossAIController>(OwnerComp.GetAIOwner());
		/*If the Controller is valid:
		1)Get the Blackboard Component and the Current Point of the bot
		2)Search for the next point, which will be different from the Current Point
		if (BossAICon)
		{
			UBlackboardComponent* BlackboardComp = BossAICon->GetBlackboardComp();
			AFinalBoss* EnemigoBoss = Cast<AFinalBoss>(BlackboardComp->GetValueAsObject("SelfActor"));

			float Distance = EnemigoBoss->DistanceToPlayer();
			if (Distance < 800.0f) {
				return EBTNodeResult::Succeeded;
			}

		}

	}
	*/
	return EBTNodeResult::Failed;
	
}