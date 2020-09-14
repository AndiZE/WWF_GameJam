// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Pollution.generated.h"

enum class EBuildingState : uint8;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UPollution : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int strenghtClean;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int rangeClean;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int strenghtDirty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int rangeDirty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int strenghtAbbadoned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int rangeAbbadoned;
private:
	int strenghtCurrent;
	int rangeCurrent;


public:
	// Sets default values for this component's properties
	UPollution();
	void SwitchPollution(EBuildingState State);
	void RemovePollution();
	UFUNCTION(BlueprintPure)
	int GetCurrentPollution() {
		return strenghtCurrent;
	}
	UFUNCTION(BlueprintPure)
	int GetCurrentRange() {
		return rangeCurrent;
	}


	//protected:
	//	// Called when the game starts
	//	virtual void BeginPlay() override;
	//
	//public:	
	//	// Called every frame
	//	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};
