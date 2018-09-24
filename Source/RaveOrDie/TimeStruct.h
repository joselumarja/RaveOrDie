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
	uint8 Tenths;

	FTimeStruct()
	{
		Seconds = Minutes = Tenths = 0;
	}

	FTimeStruct(uint8 &Tenths, uint8 &Seconds, uint8 &Minutes)
	{
		this->Seconds = Seconds;
		this->Minutes = Minutes;
		this->Tenths = Tenths;
	}

	FORCEINLINE bool operator==(const FTimeStruct &Other) const
	{
		return Seconds == Other.Seconds && Minutes == Other.Minutes && Tenths == Other.Tenths;
	}

	FORCEINLINE bool operator<=(const FTimeStruct &Other) const
	{
		if (Minutes > Other.Minutes)
		{
			return false;
		}
		else if (Seconds > Other.Seconds)
		{
			return false;
		}
		else if (Tenths > Other.Tenths)
		{
			return false;
		}
			return true;
	}
	
	
};
