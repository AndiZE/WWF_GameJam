// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cash.generated.h"

enum class EBuildingState :uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSampleDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UCash : public UActorComponent
{
	GENERATED_BODY()

public:
	int incomeClean;
	float upgradeDuration;
	int upgradeCost;
	int incomeDirty;
	int incomeAbbandoned;
	UPROPERTY(BlueprintAssignable)
		FSampleDelegate OnUpgradeFinished;
private:
	bool upgradeActive;
	FTimerHandle upgradeTimer;


public:	
	// Sets default values for this component's properties
	UCash();

	const int GetIncome(const EBuildingState State);
	void UpgradeBuilding();

	const bool IsUpgrading() {
		return upgradeActive;
	}
	const int GetUpgradeCost() {
		return upgradeCost;
	}

private:
	void UpgradeFinished();
};
