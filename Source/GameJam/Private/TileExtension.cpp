// Fill out your copyright notice in the Description page of Project Settings.


#include "TileExtension.h"

TArray<UTile*> UTileExtension::GetTilesInRange(UTile* StartTile, const int Range) {
	TArray<UTile*> openList;
	TArray<UTile*> savedList;
	int counter = Range;

	openList.Add(StartTile);
	while (counter > 0) {
		counter--;
		for (UTile* t_p : openList)
		{
			for (UTile* tn_p : t_p->neighbours)
			{
				if (tn_p && tn_p->IsValidLowLevel()) {
					savedList.AddUnique(tn_p);
				}
			}
		}
		openList = savedList;
	}
	return openList;
}
