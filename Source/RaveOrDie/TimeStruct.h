// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimeStruct.generated.h"

USTRUCT()
struct FTimeStruct
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	uint8 Seconds;

	UPROPERTY()
	uint8 Minutes;

	UPROPERTY()
	uint8 Hours;

	FTimeStruct()
	{
		Seconds = Minutes = Hours = 0;
	}

	FTimeStruct(uint8 &Seconds, uint8 &Minutes, uint8 &Hours)
	{
		this->Seconds = Seconds;
		this->Minutes = Minutes;
		this->Hours = Hours;
	}

	FORCEINLINE bool operator==(const FTimeStruct &Other) const
	{
		return Seconds == Other.Seconds && Minutes == Other.Minutes && Hours == Other.Hours;
	}

	FORCEINLINE bool operator<=(const FTimeStruct &Other) const
	{
		if (Hours > Other.Hours)
		{
			return false;
		}
		else if (Minutes > Other.Minutes)
		{
			return false;
		}
		else if (Seconds > Other.Seconds)
		{
			return false;
		}
			return true;
	}
	
	
};
