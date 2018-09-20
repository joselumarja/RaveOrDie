// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerBoxMeta.h"
#include "Engine.h"
#include "GameManager.h"
#include "RODGameStateBase.h"
#include "Subject.h"
#include "Evento.h"

void ATriggerBoxMeta::BeginPlay()
{
	Super::BeginPlay();

	MetaTriggerBoxSubject=NewObject<USubject>();
	MetaTriggerBoxSubject->AddObserver(Cast<ARODGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->GetGameManager());

}

ATriggerBoxMeta::ATriggerBoxMeta() {

	OnActorBeginOverlap.AddDynamic(this, &ATriggerBoxMeta::OnOverlapBegin);

	OnActorEndOverlap.AddDynamic(this, &ATriggerBoxMeta::OnOverlapEnd);



}



void ATriggerBoxMeta::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Dentro caja"));


	MetaTriggerBoxSubject->Notify(this, EEvent::EVENT_FINISH);
	// FIN DEL JUEGO


}


void ATriggerBoxMeta::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("Fuera caja"));

	//destruimos la caja para no lanzarla mas
	Destroy();
}



