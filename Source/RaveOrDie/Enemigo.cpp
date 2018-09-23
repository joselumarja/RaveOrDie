// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemigo.h"
#include "MyAIController.h"
#include "Engine.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "GameManager.h"
#include "EnemyBullet.h"
#include "RODCharacter.h"
#include "Subject.h"
#include "RODGameStateBase.h"
#include "Evento.h"
#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "PlayerBullet.h"


// Sets default values
AEnemigo::AEnemigo()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	//Set the peripheral vision angle to 90 degrees
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

	OnActorHit.AddDynamic(this, &AEnemigo::OnHit);

	auto FHUDWidget = ConstructorHelpers::FClassFinder<UUserWidget>(TEXT("'/Game/AI/Enemigo/WidgetEstadoEnemigo'"));

	if (FHUDWidget.Succeeded())
	{
		LifeBarWidget = FHUDWidget.Class;
	}

	pLifeBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LifeBar"));
	pLifeBarWidget->SetupAttachment(RootComponent);
	pLifeBarWidget->SetWidgetClass(LifeBarWidget);
	pLifeBarWidget->SetWorldScale3D(FVector(1.f, 0.75f, 1.f));
	pLifeBarWidget->SetRelativeLocation(FVector(0.f, 0.f, 50.f));

	MaxHealth = Health = 100.0f;
	
}

// Called when the game starts or when spawned
void AEnemigo::BeginPlay()
{
	Super::BeginPlay();

	pLifeBarWidget->InitWidget();
	LifeBar = (UProgressBar*)pLifeBarWidget->GetUserWidgetObject()->GetWidgetFromName("LifeBar");
	LifeBar->SetPercent(Health / MaxHealth);
	
	EnemySubject = NewObject<USubject>();
	EnemySubject->AddObserver(Cast<ARODGameStateBase>(UGameplayStatics::GetGameState(GetWorld()))->GetGameManager());
	PlayerPawn = Cast<ARODCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));

}

// Called every frame
void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaSeconds = DeltaTime;
}

// Called to bind functionality to input
void AEnemigo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemigo::OnSeePlayer(APawn* Pawn)
{
	AMyAIController* AIController = Cast<AMyAIController>(GetController());
	//Set the seen target on the blackboard
	if (AIController)
	{
		AIController->SetSeenTarget(Pawn);
	}
}

void AEnemigo::DeadBehaviour()
{
	LifeBar->SetVisibility(ESlateVisibility::Hidden);
	GetWorld()->GetTimerManager().SetTimer(DeadDelay, this, &AEnemigo::FinishDeadDelay, 3.3f);
	GetMesh()->PlayAnimation(DeadAnimation.Get(), false);
	GetController()->Destroy();
}

void AEnemigo::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	AMyAIController* AIController = Cast<AMyAIController>(GetController());
	if (AIController)
	{

		if (OtherActor->IsA(APlayerBullet::StaticClass()))
		{
			APlayerBullet* Bullet = Cast<APlayerBullet>(OtherActor);

			UpdateLife(Bullet->GetDamage());
			EnemySubject->Notify(this, EEvent::EVENT_SHOT_ON_TARGET);
		}
	}
}

void AEnemigo::UpdateLife(float Damage) 
{
	Health -= Damage;

	if (Health <= 0) 
	{
		DeadBehaviour();
	}
	else
	{
		LifeBar->SetPercent(Health / MaxHealth);
	}
}

void AEnemigo::FinishDeadDelay()
{
	EnemySubject->Notify(this, EEvent::EVENT_KILL);
	Destroy();
}


void AEnemigo::MoveToPlayer() 
{
	
		FVector ActualLocation = GetActorLocation();
		FVector DirectionVector = PlayerPawn->GetActorLocation() - ActualLocation;

		FVector Movement = (DirectionVector.GetSafeNormal()*(DeltaSeconds * 150));
		const FRotator NewRotation = FRotationMatrix::MakeFromX(DirectionVector).Rotator();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true);

		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}

}

float AEnemigo::DistanceToPlayer()
{
	FVector PlayerPoint = PlayerPawn->GetActorLocation();
	FVector EnemyPoint = GetActorLocation();
	float x, y, z;
	x = PlayerPoint.X - EnemyPoint.X;
	x = x * x;
	y = PlayerPoint.Y - EnemyPoint.Y;
	y = y * y;
	z = PlayerPoint.Z - EnemyPoint.Z;
	z = z * z;

	return FMath::Sqrt(x + y + z);
}

float AEnemigo::GetMeleeDamage() const
{
	return MeleeDamage;
}