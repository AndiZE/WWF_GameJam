// Fill out your copyright notice in the Description page of Project Settings.

#include "Pollution.h"
#include "CustomGameInstance.h"
#include "BaseBuilding.h"
#include "Tile.h"
#include "TileExtension.h"

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
	TArray<UTile*> affectedTiles;

	ABaseBuilding* building = Cast<ABaseBuilding>(GetOwner());
	if (building == nullptr) {
		return;
	}
	UCustomGameInstance* gameInstance = Cast<UCustomGameInstance>(building->GetGameInstance());
	if (gameInstance == nullptr) {
		return;
	}
	TArray<UTile*> tiles = gameInstance->map->FindTilesWithBuildings(building);
	for (UTile* t_p : tiles)
	{
		TArray<UTile*> rangeTiles = UTileExtension::GetTilesInRange(t_p, rangeCurrent);
		for (UTile* rt_p : rangeTiles)
		{
			affectedTiles.AddUnique(rt_p);
		}
	}
	strenghtCurrent *= -1;
	for (UTile* at_p : affectedTiles) {
		at_p->UpdatePollution(strenghtCurrent);
	}
	switch (State)
	{
	case EBuildingState::Green:
		strenghtCurrent = strenghtClean;
		rangeCurrent = rangeClean;
		break;
	case EBuildingState::Dirty:
		strenghtCurrent = strenghtDirty;
		rangeCurrent = rangeDirty;
		break;
	case EBuildingState::Abbandoned:
		strenghtCurrent = strenghtAbbadoned;
		rangeCurrent = rangeAbbadoned;
		break;
	}
	affectedTiles.Empty();
	tiles.Empty();
	tiles = gameInstance->map->FindTilesWithBuildings(building);
	for (UTile* t_p : tiles)
	{
		TArray<UTile*> rangeTiles = UTileExtension::GetTilesInRange(t_p, rangeCurrent);
		for (UTile* rt_p : rangeTiles)
		{
			affectedTiles.AddUnique(rt_p);
		}
	}
	for (UTile* at_p : affectedTiles) {
		at_p->UpdatePollution(strenghtCurrent);
	}
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

