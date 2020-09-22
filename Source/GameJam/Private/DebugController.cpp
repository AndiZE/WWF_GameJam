// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugController.h"
#include <Runtime\UMG\Public\Blueprint\WidgetBlueprintLibrary.h>

ADebugController::ADebugController() {
	bEnableClickEvents = true;
	bEnableTouchEvents = false;
	ClickEventKeys.Add(FKey("LeftMouseButton"));
	bShowMouseCursor = true;
	//UWidgetBlueprintLibrary::SetInputMode_GameAndUI(this);
}