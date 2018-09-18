// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Evento.generated.h"

UENUM()
enum class EEvent : uint8
{
	EVENT_GET_PEAR ,
	EVENT_GET_LOLLIPOP ,
	EVENT_GET_ICECREAM ,
	LAST_EVENT    
};