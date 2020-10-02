// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InfoScreen.generated.h"


class UTile;
/**
 *
 */
UCLASS(Blueprintable)
class UInfoScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateInfo(const UTile* Tile);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdateCash(const int Cash);
	UFUNCTION(BlueprintImplementableEvent)
		void UpdatePollution(const int Pollution);
	UFUNCTION(BlueprintNativeEvent)
		void UpdateProgressbar(const float MaxTime, const float ElapsedTime);
	virtual void UpdateProgressbar_Implementation(const float MaxTime, const float ElapsedTime);

};
