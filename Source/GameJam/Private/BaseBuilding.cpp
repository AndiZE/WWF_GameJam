// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"

void ABaseBuilding::DowngradeBuilding()
{
	if (state != EBuildingState)
}

void ABaseBuilding::UpgradeBuilding()
{
}

void ABaseBuilding::UpdateUI()
{
}

void ABaseBuilding::DecayBuilding()
{
}

void ABaseBuilding::ActivateToGrid()
{
}

ABaseBuilding::ABaseBuilding() 
{
	gruen = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gruen"));
	gruen->SetupAttachment(RootComponent);
	pollutionComp = CreateDefaultSubobject<UPollution>(TEXT("Pollution"));
	cashComp = CreateDefaultSubobject<UCash>(TEXT("Cash"));
}
