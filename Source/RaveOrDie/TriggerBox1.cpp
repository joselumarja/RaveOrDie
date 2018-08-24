// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerBox1.h"
#include "Engine.h"

void ATriggerBox1::BeginPlay() {
	Super::BeginPlay();
}

ATriggerBox1::ATriggerBox1() {

	OnActorBeginOverlap.AddDynamic(this, &ATriggerBox1::OnOverlapBegin);

	OnActorEndOverlap.AddDynamic(this, &ATriggerBox1::OnOverlapEnd);
}



void ATriggerBox1::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Dentro caja"));
}
void ATriggerBox1::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("Fuera caja"));

	//destruimos la caja para no lanzarla mas
	Destroy();
}



