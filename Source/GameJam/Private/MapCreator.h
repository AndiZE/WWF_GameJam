// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapCreator.generated.h"

class UTile;
class ABaseBuilding;
class UAudioComponent;
class USoundBase;

UCLASS()
class AMapCreator : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere);
	int sizeX;
	UPROPERTY(EditAnywhere);
	int sizeY;
	UPROPERTY(EditAnywhere)
	FVector startPosition;
	USoundBase* ambient;
public:
	TArray<UTile*> gridMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float gridSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float taxInterval;
	bool isDebug;
	FTimerHandle taxTimer;
	int winPollutionThreshold;
	int losePollutionThreshold;


public:	
	// Sets default values for this actor's properties
	AMapCreator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateGrid();
	void ClearGrid();
	UTile* GetTileFromGrid(int XPos, int YPos);
	void GetTilePositionFromWorldPosition(FVector WorldPosition, int& OutXPos, int& OutYPos);
	UTile* GetTileFormWorldPosition(FVector WorldPosition);
	int GetTotalPollution();
	void CollectTax();
	void RegisterBuilding();
	TArray<UTile*>FindTilesWithBuildings(ABaseBuilding* Building);
};
