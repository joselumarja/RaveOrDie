// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTEnemyShoot.h"
#include "RODCharacter.h"
#include "MyAIController.h"
#include "RangedEnemigo.h"
#include "Boss.h"
#include "MeleeEnemigo.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemigo.h"



EBTNodeResult::Type UBTTEnemyShoot::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	/*
	if (OwnerComp.GetAIOwner()->GetPawn()->IsA(AEnemigo::StaticClass())) {
		AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
		if (AICon)
		{

			UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
			AEnemigo* Enemigo = Cast<AEnemigo>(BlackboardComp->GetValueAsObject("SelfActor"));
			Enemigo->Shoot();
			//At this point, the task has been successfully completed
			return EBTNodeResult::Succeeded;
		}
	}

	else if (OwnerComp.GetAIOwner()->GetPawn()->IsA(AFinalBoss::StaticClass())) {
		ABossAIController* BossAICon = Cast<ABossAIController>(OwnerComp.GetAIOwner());
		if (BossAICon)
		{
			UBlackboardComponent* BlackboardComp = BossAICon->GetBlackboardComp();
			AFinalBoss* EnemigoBoss = Cast<AFinalBoss>(BlackboardComp->GetValueAsObject("SelfActor"));

			EnemigoBoss->Shoot();
			return EBTNodeResult::Succeeded;
		}

	}
	*/
	return EBTNodeResult::Failed;
}