// Fill out your copyright notice in the Description page of Project Settings.

#include "BossAIController.h"
#include "FinalBoss.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


ABossAIController::ABossAIController() {
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void ABossAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);
	//Get the possessed Pawn. If it's the AI Character we created
	//initialize it's blackboard and start it's corresponding behavior tree
	AFinalBoss* AICharacter = Cast<AFinalBoss>(Pawn);
	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
			BehaviorComp->StartTree(*AICharacter->BehaviorTree);
		}
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsObject("SelfActor", Pawn);
		}
	}
}

void ABossAIController::SetSeenTarget(APawn* Pawn)
{
	//Registers the Pawn that the AI has seen in the blackboard
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(BlackboardKey, Pawn);
	}
}


