// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DebugUI.generated.h"

class UTile;

/**
 *
 */
UCLASS()
class UDebugUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		void UpdateGridText(int XPos, int YPos, UTile* Tile);
};
