// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerBox1.h"
#include "Enemigo.h"
#include "FinalBoss.h"
#include "MyAIController.h"
#include "Engine.h"

void ATriggerBox1::BeginPlay() {
	Super::BeginPlay();
}

ATriggerBox1::ATriggerBox1() {

	OnActorBeginOverlap.AddDynamic(this, &ATriggerBox1::OnOverlapBegin);

	OnActorEndOverlap.AddDynamic(this, &ATriggerBox1::OnOverlapEnd);


	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("/Game/AI/Enemigo/BP_Enemigo.BP_Enemigo"));
	if (ItemBlueprint.Object) {
		MyItemBlueprint = (UClass*)ItemBlueprint.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> RangedItemBlueprint(TEXT("/Game/AI/Enemigo/BP_Enemigo_Ranged.BP_Enemigo_Ranged"));
	if (RangedItemBlueprint.Object) {
		MyRangedBlueprint = (UClass*)RangedItemBlueprint.Object->GeneratedClass;
	}


	static ConstructorHelpers::FObjectFinder<UBlueprint> BossItemBlueprint(TEXT("/Game/AI/FinaBoss/BPFinalBoss.BPFinalBoss"));
	if (BossItemBlueprint.Object) {
		MyBossBlueprint = (UClass*)BossItemBlueprint.Object->GeneratedClass;
	}
}



void ATriggerBox1::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Dentro caja"));
	
	FVector RandomLocation(1500.f, 1000.f, 108.f);
	FRotator Rotation(0.0f, 180.0f, 0.0f);

	//AEnemigo* DroppedItem = GetWorld()->SpawnActor<AEnemigo>(MyItemBlueprint, RandomLocation, Rotation);
	AFinalBoss* DroppedItem = GetWorld()->SpawnActor<AFinalBoss>(MyBossBlueprint, RandomLocation, Rotation);
	
}
void ATriggerBox1::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Black, TEXT("Fuera caja"));

	//destruimos la caja para no lanzarla mas
	Destroy();
}



