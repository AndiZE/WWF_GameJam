// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InfoScreen.generated.h"


class UTile;
/**
 *
 */
UCLASS()
class UInfoScreen : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateInfo(UTile* Tile);
	UFUNCTION(BlueprintCallable)
		void UpdateCash(int Cash);
	UFUNCTION(BlueprintCallable)
		void UpdatePollution(int Pollution);
	UFUNCTION(BlueprintCallable)
		void UpdateProgressbar(float MaxTime, float ElapsedTime);

};
