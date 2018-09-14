// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTEnemyShoot.h"
#include "RODCharacter.h"
#include "MyAIController.h"
#include "Enemigo.h"
#include "RangedEnemigo.h"
#include "Boss.h"
#include "MeleeEnemigo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemigo.h"



EBTNodeResult::Type UBTTEnemyShoot::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
		AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
		if (AICon)
		{

			UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
			AEnemigo* Enemigo = Cast<AEnemigo>(BlackboardComp->GetValueAsObject("SelfActor"));
			Enemigo->Shoot();
			//At this point, the task has been successfully completed
			return EBTNodeResult::Succeeded;
		}

	
	return EBTNodeResult::Failed;
}