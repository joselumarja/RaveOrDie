// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimeStruct.h"
#include "SaveGameStruct.generated.h"

USTRUCT()
struct FSaveGameStruct
{
	GENERATED_BODY()
public:

	UPROPERTY()
		FText PlayerName;

	UPROPERTY()
		int32 Kills;

	UPROPERTY()
		float Accuracy;

	UPROPERTY()
		FTimeStruct PlayTime;

	FSaveGameStruct()
	{
		this->PlayerName = FText();
		this->Kills = 0;
		this->Accuracy = 0.f;
		this->PlayTime = FTimeStruct();
	}

	FSaveGameStruct(FText &PlayerName, uint32 &Kills, float &Accuracy, FTimeStruct &PlayTime)
	{
		this->PlayerName = PlayerName;
		this->Kills = Kills;
		this->Accuracy = Accuracy;
		this->PlayTime = PlayTime;

	}

	FORCEINLINE bool operator<(const FSaveGameStruct &Other) const
	{
		if (PlayTime <= Other.PlayTime)
		{
			if (PlayTime == Other.PlayTime)
			{
				if (Kills > Other.Kills)
				{
					return true;
				}

				return false;
			}

			return true;
		}

		return false;
	}

	FORCEINLINE bool operator==(const FSaveGameStruct &Other) const
	{
		return PlayTime == Other.PlayTime && Kills==Other.Kills;
	}

};