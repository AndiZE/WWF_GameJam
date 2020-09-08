// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DebugPlayer.generated.h"

class AMapCreator;
class UTile;
UCLASS()
class ADebugPlayer : public APawn
{
	GENERATED_BODY()

public:
	int playerCash;
	int startMoney;
	//Camera
	float cameraSpeed;
	float cameraZoomMin;
	float cameraZoomMax;
	float cameraZoomStep;

	//ui debugUI;
	//ui infoHud;
	AMapCreator* map;
	//Gameinstance gameInstance;
	bool isDebug;
	UTile* currentSelectedTile;

public:
	// Sets default values for this pawn's properties
	ADebugPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddCash(int Cash);
	void SelectTile(UTile* Tile);
	void DeselectTile();
	bool CanSpendCash(int Cost);
};
