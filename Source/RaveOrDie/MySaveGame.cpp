// Fill out your copyright notice in the Description page of Project Settings.

#include "MySaveGame.h"

#define LOCTEXT_NAMESPACE "MySaveGame"

int32 UMySaveGame::GetIndexName() const
{
	return UserIndex;
}

FString UMySaveGame::GetSlotName()const
{
	return SaveSlotName;
}

UMySaveGame::UMySaveGame()
{
	SaveSlotName = TEXT("TestSaveSlot");
	UserIndex = 0;
}

FText UMySaveGame::GetRecordNames()const
{
	FText String;

	for (int i = 0; i < Records.Num(); i++)
	{
		String = FText::Format(LOCTEXT("Names", "{0}{1}\n"), String, Records[i].PlayerName);
	}

	return String;
}

FText UMySaveGame::GetRecordAccuracy() const
{
	FText String;

	for (int i = 0; i < Records.Num(); i++)
	{
		String = FText::Format(LOCTEXT("Accuracy", "{0}{1}\n"), String, FText::AsNumber(Records[i].Accuracy));
	}

	return String;
}

FText UMySaveGame::GetRecordTime() const
{
	FText String;

	for (int i = 0; i < Records.Num(); i++)
	{
		String = FText::Format(LOCTEXT("KilledEnemies", "{0}{1}:{2}:{3}\n"), String, FText::AsNumber(Records[i].PlayTime.Minutes), FText::AsNumber(Records[i].PlayTime.Seconds), FText::AsNumber(Records[i].PlayTime.Tenths));
	}

	return String;
}



FText UMySaveGame::GetRecordKills()const
{
	FText String;

	for (int i = 0; i < Records.Num(); i++)
	{
		String = FText::Format(LOCTEXT("Kills", "{0}{1}\n"), String, FText::AsNumber(Records[i].Kills));
	}

	return String;
}
void UMySaveGame::UpdateRecords(FText &name, uint32 &Kills, float &Accuracy, FTimeStruct &PlayTime)
{
	FSaveGameStruct NewSave = FSaveGameStruct(name, Kills, Accuracy, PlayTime);
	Records.Add(NewSave);
	Records.Sort();
}

#undef LOCTEXT_NAMESPACE



