// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DebugPlayer.generated.h"

class AMapCreator;
class UTile;
class UDebugUI;
class UInfoScreen;
class USpringArmComponent;
class UCineCameraComponent;
class UCustomGameInstance;

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
	bool isDebug;
	UPROPERTY()
		UDebugUI* debugUI;
	UPROPERTY()
		UInfoScreen* infoHud;
	UPROPERTY()
		AMapCreator* map;
	UPROPERTY()
		UCustomGameInstance* gameInstance;
	UPROPERTY()
		UTile* currentSelectedTile;

	UPROPERTY()
		USpringArmComponent* springArm;
	UPROPERTY()
		UCineCameraComponent* cineCam;


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
	void MoveHorizontal(float AxisValue);
	void MoveVertical(float AxisValue);
	void AddCash(int Cash);
	void SelectTile(UTile* Tile);
	void DeselectTile();
	bool CanSpendCash(int Cost);
	void AddMovement(FVector Input);
	void ZoomCamera(float MouseWheelAxisValue);
};
