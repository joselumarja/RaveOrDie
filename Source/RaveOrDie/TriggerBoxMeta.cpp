// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerBoxMeta.h"
#include "Engine.h"
#include "GameManager.h"
#include "RODGameStateBase.h"
#include "Subject.h"
#include "RODCharacter.h"
#include "Evento.h"

void ATriggerBoxMeta::BeginPlay()
{
	Super::BeginPlay();
	MetaTriggerBoxSubject=NewObject<USubject>();
	MetaTriggerBoxSubject->AddObserver(Cast<ARODGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->GetGameManager());
}

ATriggerBoxMeta::ATriggerBoxMeta() {
	OnActorBeginOverlap.AddDynamic(this, &ATriggerBoxMeta::OnOverlapBegin);
}



void ATriggerBoxMeta::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor) {

	ARODCharacter* RODCharacter = Cast<ARODCharacter>(OtherActor);
	if (RODCharacter)
	{
		MetaTriggerBoxSubject->Notify(this, EEvent::EVENT_FINISH);
		MarkPendingKill();
	}

}






