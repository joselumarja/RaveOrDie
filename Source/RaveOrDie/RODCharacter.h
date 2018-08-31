// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Animation/BlendSpace.h"
#include "RODCharacter.generated.h"

UCLASS(Blueprintable)
class RAVEORDIE_API ARODCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARODCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE bool IsInMeleeAttack() const { return bIsInMeleeAttack; }

	FORCEINLINE bool GetCanAttack() const { return bCanMeleeAttack; }

	float GetMeleeDamage() const;

	void MeleeAttack();

	void DistanceAttack();

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float InvulnerabilityTime;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float HitInvulnerabilityTime;

	void InvulnerabilityTimerExpired();

	void HitInvulnerabilityExpired();

	void SetHitInvulnerability();

	void SetInvulnerability();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		bool CanMeleeAttack = false;


	void FinishMeleeAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	
	bool bInvulnerability = false;

	bool bCanMeleeAttack=true;

	bool bIsInMeleeAttack;


	void FinishDistanceAttack();

	FTimerHandle TimerHandle_InvulnerabilityHitExpired;

	FTimerHandle TimerHandle_InvulnerabilityExpired;
	
	UWorld* World;

};
