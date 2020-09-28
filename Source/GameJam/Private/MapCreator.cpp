// Fill out your copyright notice in the Description page of Project Settings.


#include "MapCreator.h"
#include "Tile.h"
#include "BaseBuilding.h"
#include "Cash.h"
#include "DebugPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "CustomGameInstance.h"
#include "Sound/SoundCue.h"
#include "InfoScreen.h"
#include "Blueprint/UserWidget.h"
#include "Tutorial.h"
#include "Win.h"
#include "LosePollution.h"

// Sets default values
AMapCreator::AMapCreator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	auto soundFile = ConstructorHelpers::FObjectFinder<USoundBase>(TEXT("SoundCue'/Game/Audio/Creepy_Ambience_LOOP'"));
	if (soundFile.Object != nullptr)
	{
		ambient = soundFile.Object;
	}
}

// Called when the game starts or when spawned
void AMapCreator::BeginPlay()
{
	Super::BeginPlay();
	UCustomGameInstance* gameInstance = Cast<UCustomGameInstance>(GetGameInstance());
	if (gameInstance == nullptr) {
		return;
	}
	gameInstance->map = this;
	CreateGrid();
	gameInstance->camMinPos = GetActorLocation();
	gameInstance->camMaxPos = GetActorLocation() + FVector(sizeX * gridSize, sizeY * gridSize, 0.0f);
	GetWorldTimerManager().SetTimer(taxTimer, this, &AMapCreator::CollectTax, taxInterval, true);
	UGameplayStatics::PlaySound2D(this, ambient);
	RegisterBuilding();
	UUserWidget* tutorial = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), UTutorial::StaticClass());
	tutorial->AddToViewport();
	player = Cast<ADebugPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
	roadInstance = GetWorld()->GetParameterCollectionInstance(roadParams);
}

// Called every frame
void AMapCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	player->infoHud->UpdateProgressbar(taxInterval, GetWorldTimerManager().GetTimerElapsed(taxTimer));
	int tPollution = GetTotalPollution();
	player->infoHud->UpdatePollution(tPollution);
		roadInstance->SetScalarParameterValue("Dirtyness", 0.0f);
		if (tPollution <= winPollutionThreshold) {
			if (!endActivted) {
				endActivted = true;
				UUserWidget* tutorial = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), UWin::StaticClass());
				tutorial->AddToViewport();
			}
		}
		else if (tPollution >= losePollutionThreshold){
			if (!endActivted) {
				endActivted = true;
				UUserWidget* tutorial = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), ULosePollution::StaticClass());
				tutorial->AddToViewport();
			}
		}
}

void AMapCreator::CreateGrid()
{
	startPosition = FVector(0.0f);
	ClearGrid();
	for (size_t y = 0; y < sizeY; y++)
	{
		for (size_t x = 0; x < sizeX; x++)
		{
			UTile* tile = NewObject<UTile>(this, UTile::StaticClass());
			tile->neighbours.SetNumUninitialized(4);
			for (UTile* tileP : tile->neighbours)
			{
				tileP = nullptr;
			}
			tile->posX = x;
			tile->posY = y;
			tile->worldPosition = startPosition + FVector(gridSize * x + gridSize * 0.5f, gridSize * y + gridSize * 0.5f, 0.0f);

			if (x > 0) {
				tile->SetNeigbours(GetTileFromGrid(x - 1, y), ETileDirection::South);
			}
			if (y > 0) {
				tile->SetNeigbours(GetTileFromGrid(x, y - 1), ETileDirection::West);
			}
			gridMap.Add(tile);
		}
	}
	startPosition = FVector(1.0f);
}

void AMapCreator::ClearGrid()
{
	for (UTile* tile : gridMap) {
		tile->neighbours.Empty();
	}
	gridMap.Empty();
}

UTile* AMapCreator::GetTileFromGrid(int XPos, int YPos)
{
	return gridMap[sizeX * YPos + XPos];
}

void AMapCreator::GetTilePositionFromWorldPosition(FVector WorldPosition, int& OutXPos, int& OutYPos)
{
	FVector pos = WorldPosition - GetActorLocation();
	OutXPos = FMath::Clamp(FMath::TruncToInt(pos.X / gridSize), 0, sizeX - 1);
	OutYPos = FMath::Clamp(FMath::TruncToInt(pos.Y / gridSize), 0, sizeY - 1);
}

UTile* AMapCreator::GetTileFormWorldPosition(FVector WorldPosition)
{
	int x = 0;
	int y = 0;
	GetTilePositionFromWorldPosition(WorldPosition, x, y);
	return GetTileFromGrid(x, y);
}

int AMapCreator::GetTotalPollution()
{
	int sumPollution = 0;
	for (UTile* elem : gridMap)
	{
		sumPollution += elem->GetPollution();
	}
	return sumPollution;
}

void AMapCreator::CollectTax()
{
	TArray<ABaseBuilding*> buildings;
	int taxCollected = 0;
	for (UTile* tile : gridMap)
	{
		if (tile->GetBuilding()->IsValidLowLevel())
		{
			buildings.Add(tile->GetBuilding());
		}
	}
	for (ABaseBuilding* building : buildings) {
		if (!building->cashComp->IsUpgrading()) {
			taxCollected += building->cashComp->GetIncome(building->state);

		}
	}
	if (player != nullptr) {
		player->AddCash(taxCollected);
	}

}

void AMapCreator::RegisterBuilding()
{
	TArray<AActor*> buildings;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseBuilding::StaticClass(), buildings);
	for (AActor* obj : buildings)
	{
		ABaseBuilding* building = Cast<ABaseBuilding>(obj);
		if (building != nullptr) {
			building->ActivateToGrid();
		}
	}
}

TArray<UTile*> AMapCreator::FindTilesWithBuildings(ABaseBuilding* Building)
{
	TArray<UTile*> tiles;
	for (UTile* elem : gridMap) {
		if (elem->GetBuilding() == Building) {
			tiles.Add(elem);
		}
	}
	return tiles;
}

