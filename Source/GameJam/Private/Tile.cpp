// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "BaseBuilding.h"

void UTile::SetNeigbours(UTile* Tile, ETileDirection direction)
{
	neighbours[(int)direction] = Tile;
	Tile->neighbours[(int)UTileDirectionExtension::GetOpposite(direction)] = this;
}

void UTile::SetBuilding(ABaseBuilding* NewBuilding)
{
	building = NewBuilding;
	building->state = EBuildingState::Dirty;
	building->pollutionComp->SwitchPollution(EBuildingState::Dirty);
}

void UTile::UpdatePollution(int Pollution)
{
	curPollution += Pollution;
}

