// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BuildingState.h"
#include "Pollution.h"
#include "Cash.h"
#include "BaseBuilding.generated.h"

class ADebugPlayer;
class UStaticMeshComponent;
class UParticleSystemComponent;
class UCustomGameInstance;


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
		UStaticMeshComponent* gruen = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UParticleSystemComponent* dust = nullptr;
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
		EBuildingState state;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString buildingName;


private:
	UPROPERTY()
		FTimerHandle decayTimer;
	UPROPERTY()
		ADebugPlayer* player;
	UPROPERTY()
		UCustomGameInstance* gameInstance;
public:
	virtual void BeginPlay() override;
	UFUNCTION()
		void DowngradeBuilding();
	UFUNCTION(BlueprintCallable)
		void UpgradeBuilding();
	UFUNCTION(BlueprintCallable)
		void UpdateUI();
	UFUNCTION()
		void DecayBuilding();
	UFUNCTION()
		void ActivateToGrid();
	UFUNCTION()
		void OnMeshClicked(UPrimitiveComponent* Target, FKey ButtonPressed);
};
