// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Materials/MaterialParameterCollection.h"
#include "MapCreator.generated.h"

class UTile;
class ABaseBuilding;
class UAudioComponent;
class USoundBase;
class ADebugPlayer;

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
	UPROPERTY()
		USoundBase* ambient;
	UPROPERTY()
		ADebugPlayer* player;
	bool endActivted = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	UMaterialParameterCollectionInstance* roadInstance;
	UPROPERTY()
	TArray<UTile*> gridMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float gridSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	float taxInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool isDebug;
	FTimerHandle taxTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int winPollutionThreshold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int losePollutionThreshold;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	UMaterialParameterCollection* roadParams;


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
