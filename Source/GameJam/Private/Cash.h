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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int incomeClean;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float upgradeDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int upgradeCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int incomeDirty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int incomeAbbandoned;
	UPROPERTY(BlueprintAssignable)
		FSampleDelegate OnUpgradeFinished;
private:
	bool upgradeActive;
	UPROPERTY()
	FTimerHandle upgradeTimer;


public:	
	// Sets default values for this component's properties
	UCash();
	UFUNCTION(BlueprintPure)
		const int GetIncome(const EBuildingState State);
	void UpgradeBuilding();

	const bool IsUpgrading() {
		return upgradeActive;
	}
	UFUNCTION(BlueprintPure)
	const int GetUpgradeCost() {
		return upgradeCost;
	}

private:
	void UpgradeFinished();
};
