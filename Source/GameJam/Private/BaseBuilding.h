// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BuildingState.h"
#include "DebugPlayer.h"
#include "Cash.h"
#include "Pollution.h"
#include "BaseBuilding.generated.h"


/**
 * 
 */
UCLASS()
class ABaseBuilding : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ABaseBuilding();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* gruen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCash* cashComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UPollution* pollutionComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int tileSizeX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int tileSizeY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float tileSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float decayTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FTimerHandle decayTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBuildingState state;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ADebugPlayer* player;


public:
	UFUNCTION (BlueprintCallable)
		void DowngradeBuilding();
	UFUNCTION (BlueprintCallable)
		void UpgradeBuilding();
	UFUNCTION(BlueprintCallable)
		void UpdateUI();
	UFUNCTION(BlueprintCallable)
		void DecayBuilding();
	UFUNCTION(BlueprintCallable)
		void ActivateToGrid();
};
