// Fill out your copyright notice in the Description page of Project Settings.

#include "BTChangeBT.h"
#include "RODCharacter.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemigo.h"


EBTNodeResult::Type UBTChangeBT::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

		//At this point, the task has been successfully completed
		return EBTNodeResult::Succeeded;
}
