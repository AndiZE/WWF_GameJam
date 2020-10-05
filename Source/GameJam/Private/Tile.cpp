// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "BaseBuilding.h"

UTile::UTile()
{
}

void UTile::SetNeigbours(UTile* Tile, ETileDirection direction)
{
	neighbours[(int)direction] = Tile;
	Tile->neighbours[(int)UTileDirectionExtension::GetOpposite(direction)] = this;
}

void UTile::SetBuilding(ABaseBuilding* NewBuilding)
{
	building = NewBuilding;
	if (building)
	{
		building->state = EBuildingState::Dirty;

		if (building->pollutionComp->IsValidLowLevel())
			building->pollutionComp->SwitchPollution(building->state);
	}
}

void UTile::UpdatePollution(int Pollution)
{
	curPollution += Pollution;
}

