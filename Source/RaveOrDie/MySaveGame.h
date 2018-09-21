// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameStruct.h"
#include "TimeStruct.h"
#include "MySaveGame.generated.h"

UCLASS()
class RAVEORDIE_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = SaveGame)
		FString GetSlotName() const;

	UFUNCTION(BlueprintCallable, Category = SaveGame)
		int32 GetIndexName() const;

	UFUNCTION(BlueprintCallable, Category = SaveGame)
		FText GetRecordNames() const;

	UFUNCTION(BlueprintCallable, Category = SaveGame)
		FText GetRecordKills() const;

	UFUNCTION(BlueprintCallable, Category = SaveGame)
		FText GetRecordAccuracy() const;

	UFUNCTION(BlueprintCallable, Category = SaveGame)
		FText GetRecordTime() const;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		TArray<FSaveGameStruct> Records;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Basic)
		int32 UserIndex;

	UMySaveGame();

	void UpdateRecords(FText &name, uint32 &Kills,float &Accuracy,FTimeStruct &PlayTime);

	
};
