// Fill out your copyright notice in the Description page of Project Settings.


#include "TileExtension.h"

void UTileExtension::GetTilesInRange(UTile* StartTile, const int Range, TArray<UTile*> &outTiles) {
	TArray<UTile*> openList;
	//TArray<UTile*> savedList;
	int counter = Range;

	openList.Add(StartTile);
	while (counter > 0) {
		counter--;
		for (UTile*& t_p : openList)
		{
			if (t_p->IsValidLowLevelFast())
			{
				for (UTile*& tn_p : t_p->neighbours)
				{
					if (tn_p->IsValidLowLevelFast()) {
						outTiles.AddUnique(tn_p);
					}
				}
			}
		}
		openList = outTiles;
	}
}
