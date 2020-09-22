// Fill out your copyright notice in the Description page of Project Settings.


#include "GMBase.h"
#include "DebugPlayer.h"
#include "DebugController.h"

AGMBase::AGMBase()
{
	PlayerControllerClass = ADebugController::StaticClass();
	DefaultPawnClass = ADebugPlayer::StaticClass();
}