// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugPlayer.h"

// Sets default values
ADebugPlayer::ADebugPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADebugPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADebugPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADebugPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

