// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameInstance.h"
#include "BaseBuilding.h"
#include "Tile.h"
#include "Pollution.h"

// Sets default values for this component's properties
UPollution::UPollution()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPollution::SwitchPollution(EBuildingState State)
{
	ABaseBuilding* building = Cast<ABaseBuilding>(GetOwner());
	if (building == nullptr) {
		return;
	}
	UCustomGameInstance* gameInstance = Cast<UCustomGameInstance>(building->GetGameInstance());
	if (gameInstance == nullptr) {
		return;
	}
	//TArray<UTile*> tiles = gameInstance->map->FindTilesWithBuilding(building);
}


void UPollution::RemovePollution()
{
}


//// Called when the game starts
//void UPollution::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//	
//}
//
//
//// Called every frame
//void UPollution::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

