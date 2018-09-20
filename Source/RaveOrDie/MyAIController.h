// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MyAIController.generated.h"


UCLASS()
class RAVEORDIE_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMyAIController();

	//Behavior tree comp ref
	UBehaviorTreeComponent* BehaviorComp;

	//Blackboard comp ref
	UBlackboardComponent* BlackboardComp;

	virtual void Possess(APawn* Pawn) override;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BlackboardKey = "Target";


	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }

	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeComp() const { return BehaviorComp; }

	//Sets the sensed target in the blackboard
	void SetSeenTarget(APawn* Pawn);


};
