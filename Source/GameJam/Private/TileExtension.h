// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tile.h"
#include "TileExtension.generated.h"
/**
 * 
 */
UCLASS()
class UTileExtension : public UObject
{
	GENERATED_BODY()
public:
	static void GetTilesInRange(UTile* StartTile, const int Range, TArray<UTile*>& outTiles);
};
