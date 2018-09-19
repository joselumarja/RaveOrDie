// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Evento.generated.h"

UENUM()
enum class EEvent : uint8
{
	EVENT_SHOT ,
	EVENT_SHOT_ON_TARGET ,
	EVENT_KILL,
	EVENT_DEAD,
	EVENT_FINISH
};