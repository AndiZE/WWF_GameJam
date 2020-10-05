// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuildingState.h"
#include "Pollution.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UPollution : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int strenghtClean = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int rangeClean = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int strenghtDirty = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int rangeDirty = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int strenghtAbbadoned = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int rangeAbbadoned = 0;
private:
	int strenghtCurrent = 0;;
	int rangeCurrent = 0;

public:
	// Sets default values for this component's properties
	UPollution();
	void SwitchPollution(EBuildingState State);
	UFUNCTION()
	const int GetCurrentPollution() {
		return strenghtCurrent;
	}
	UFUNCTION()
	const int GetCurrentRange() {
		return rangeCurrent;
	}
};
