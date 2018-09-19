// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Array.h"
#include "Evento.h"
#include "Subject.generated.h"

class IObserver;

UCLASS()
class RAVEORDIE_API USubject : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Observer Pattern")
	void AddObserver(TScriptInterface<IObserver> Observer);

	UFUNCTION(BlueprintCallable, Category = "Observer Pattern")
	void RemoveObserver(TScriptInterface<IObserver> Observer);

	UFUNCTION(BlueprintCallable, Category = "Observer Pattern")
	void Notify(UObject* Entity, EEvent Event);

private:
	// UINTERFACES generate their destructor private,
	// so shared pointer can't access it to manage its life cycle,
	// thus giving us an error at compile time if we try to use them.
	TArray<IObserver*> Observers;
	
	
};
