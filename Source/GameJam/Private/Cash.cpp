// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingState.h"
#include "Cash.h"

// Sets default values for this component's properties
UCash::UCash()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

const int UCash::GetIncome(const EBuildingState State)
{
	int income = 0;
	switch (State)
	{
	case EBuildingState::Green:
		income = incomeClean;
		break;
	case EBuildingState::Dirty:
		income = incomeDirty;
		break;
	case EBuildingState::Abbandoned:
		income = incomeAbbandoned;
		break;
	}
	return income;
}

void UCash::UpgradeBuilding()
{
	if (!upgradeActive) {
	
		upgradeActive = true;
		GetWorld()->GetTimerManager().SetTimer(upgradeTimer, this, &UCash::UpgradeFinished, upgradeDuration, false);
	}
}

void UCash::UpgradeFinished()
{
	upgradeActive = true;
	OnUpgradeFinished.Broadcast();
}

