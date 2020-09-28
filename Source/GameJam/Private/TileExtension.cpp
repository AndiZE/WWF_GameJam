// Fill out your copyright notice in the Description page of Project Settings.


#include "TileExtension.h"

TArray<UTile*> UTileExtension::GetTilesInRange(UTile* StartTile, const int Range) {
	TArray<UTile*> openList;
	TArray<UTile*> savedList;
	int counter = Range;

	openList.Add(StartTile);
	while (counter > 0) {
		counter--;
		for (UTile*& t_p : openList)
		{
			//for (size_t i = 0; i < t_p->neighbours.Num(); i++)
			//{
			//	if (t_p->neighbours[i] != nullptr && t_p->neighbours[i]->IsValidLowLevel()) {
			//		savedList.AddUnique(t_p->neighbours[i]);
			//	}
			//}
			for (UTile*& tn_p : openList)
			{
				if (tn_p->IsValidLowLevel()) {
					savedList.AddUnique(tn_p);
				}
			}
		}
		openList = savedList;
	}
	return openList;
}
