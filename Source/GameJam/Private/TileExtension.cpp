// Fill out your copyright notice in the Description page of Project Settings.


#include "TileExtension.h"

void UTileExtension::GetTilesInRange(UTile* StartTile, const int Range, TArray<UTile*> &outTiles) {
	TArray<UTile*> openList;
	//int counter = Range;

	openList.Add(StartTile);
	for (size_t counter = 0; counter < Range; counter++)
	{
		for (UTile*& t_p : openList)
		{
			if (IsValid(t_p))
			{
				for (UTile*& tn_p : t_p->neighbours)
				{
					if (IsValid(tn_p)) {
						outTiles.AddUnique(tn_p);
					}
				}
			}
		}
		openList = outTiles;
	}
}
