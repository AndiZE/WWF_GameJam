// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TileDirection.h"
#include "BuildingState.h"
#include "BaseBuilding.h"
#include "Tile.generated.h"

/**
 *
 */
UCLASS()
class UTile : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
		ABaseBuilding* building;
	UPROPERTY(VisibleAnywhere)
		int curPollution;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UTile*> neighbours;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector worldPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int posX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int posY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float income;

public:
	UTile(const class FObjectInitializer& obj);

	void Init(const int X, const int Y, const FVector WorldPosition);
	UFUNCTION(BlueprintCallable)
		void SetNeigbours(UTile* Tile, ETileDirection direction);
	UFUNCTION(BlueprintPure)
		int GetPollution() { return curPollution; };
	UFUNCTION(BlueprintPure)
		float GetIncome() { return income; };
	UFUNCTION(BlueprintCallable)
		ABaseBuilding* GetBuilding() { return building; };
	UFUNCTION(BlueprintCallable)
		 void SetBuilding(ABaseBuilding* NewBuilding);
	UFUNCTION(BlueprintCallable)
		void UpdatePollution(int Pollution);
};
