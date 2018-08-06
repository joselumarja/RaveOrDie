// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"
#include "Enemigo.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


AMyAIController::AMyAIController() {
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

void AMyAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);
	//Get the possessed Pawn. If it's the AI Character we created
	//initialize it's blackboard and start it's corresponding behavior tree
	AEnemigo* AICharacter = Cast<AEnemigo>(Pawn);
	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
			BehaviorComp->StartTree(*AICharacter->BehaviorTree);
		}
	}
}

void AMyAIController::SetSeenTarget(APawn* Pawn)
{
	//Registers the Pawn that the AI has seen in the blackboard
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(BlackboardKey, Pawn);
	}
}

