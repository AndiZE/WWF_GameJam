// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MapCreator.h"
#include "CustomGameInstance.generated.h"

/**
 *
 */
UCLASS()
class UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AMapCreator* map = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector camMinPos;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector camMaxPos;
};
