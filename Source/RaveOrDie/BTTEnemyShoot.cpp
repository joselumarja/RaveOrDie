// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTEnemyShoot.h"
#include "FinalBoss.h"
#include "BossAIController.h"
#include "RODCharacter.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemigo.h"



EBTNodeResult::Type UBTTEnemyShoot::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	if (OwnerComp.GetAIOwner()->GetPawn()->IsA(AEnemigo::StaticClass())) {
		AMyAIController* AICon = Cast<AMyAIController>(OwnerComp.GetAIOwner());
		/*If the Controller is valid:
		1)Get the Blackboard Component and the Current Point of the bot
		2)Search for the next point, which will be different from the Current Point*/
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
		/*If the Controller is valid:
		1)Get the Blackboard Component and the Current Point of the bot
		2)Search for the next point, which will be different from the Current Point*/
		if (BossAICon)
		{
			UBlackboardComponent* BlackboardComp = BossAICon->GetBlackboardComp();
			AFinalBoss* EnemigoBoss = Cast<AFinalBoss>(BlackboardComp->GetValueAsObject("SelfActor"));

			EnemigoBoss->Shoot();
			return EBTNodeResult::Succeeded;
		}

	}

	return EBTNodeResult::Failed;
}