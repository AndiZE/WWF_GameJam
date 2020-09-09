// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBuilding.h"

void ABaseBuilding::DowngradeBuilding()
{
	//Clear timer after Call for reusing
	GetWorldTimerManager().ClearTimer(decayTimer);
	if (state == EBuildingState::Abbandoned)
	{
		return;
	}
	switch (state)
	{
	case EBuildingState::Green:
		state = EBuildingState::Dirty;
		gruen->SetVisibility(false);
		break;
	case EBuildingState::Dirty:
		state = EBuildingState::Abbandoned;
		GetWorldTimerManager().ClearTimer(decayTimer);
		break;
		//case EBuildingState::Abbandoned:
		//	break;
	}
	GetStaticMeshComponent()->SetScalarParameterValueOnMaterials("DirtOverlay", 0.0f);
	pollutionComp->SwitchPollution(state);
	UpdateUI();
}

void ABaseBuilding::UpgradeBuilding()
{
	if (state == EBuildingState::Green)
	{
		return;
	}
	if (player->CanSpendCash(cashComp->upgradeCost))
	{
		switch (state)
		{
			//case EBuildingState::Green:
			//	break;
		case EBuildingState::Dirty:
			state = EBuildingState::Green;
			gruen->SetVisibility(true);
			GetStaticMeshComponent()->SetScalarParameterValueOnMaterials("DirtOverlay", 0.0f);
			dust->Activate(true);
			GetWorldTimerManager().ClearTimer(decayTimer);
			break;
		case EBuildingState::Abbandoned:
			state = EBuildingState::Dirty;
			GetStaticMeshComponent()->SetScalarParameterValueOnMaterials("DirtOverlay", 0.5f);
			dust->Activate(true);
			GetWorldTimerManager().SetTimer(decayTimer, this, &ABaseBuilding::DowngradeBuilding, decayTime, false);
			break;
		}
		pollutionComp->SwitchPollution(state);
		UpdateUI();
	}
}

void ABaseBuilding::UpdateUI()
{
	UCustomGameInstance* gameInstance = Cast<UCustomGameInstance>(GetGameInstance());
	if (gameInstance != nullptr) {
		UTile* tile = gameInstance->map->GetTileFormWorldPosition(GetActorLocation());
		player->SelectTile(tile);
	}
}

void ABaseBuilding::DecayBuilding()
{
	ABaseBuilding::DowngradeBuilding();
}

void ABaseBuilding::ActivateToGrid()
{
	FHitResult* hit = nullptr;
	FVector offset = FVector(0.0f, 0.0f, 0.0f);
	UCustomGameInstance* gameInstance = Cast<UCustomGameInstance>(GetGameInstance());
	if (tileSizeX == 1) {
		offset += FVector(tileSize * 0.5f, 0.0f, 0.0f);
	}
	if (tileSizeY == 1) {
		offset += FVector(0.0f, tileSize * 0.5f, 0.0f);
	}

	for (size_t y = 0; y < tileSizeY - 1; y++)
	{
		for (size_t x = 0; x < tileSizeX - 1; x++)
		{
			offset += FVector(x * tileSize - tileSize * 0.5f, y * tileSize - tileSize * 0.5f, 0.0f) + GetActorLocation();
			GetWorld()->LineTraceSingleByChannel(*hit, offset, GetActorUpVector() * 400.0f + offset, ECollisionChannel::ECC_Visibility);

			if (hit != nullptr) {
				//gameInstance->map->GetTileFromWorldPosition()->SetBuilding(this);
				GetWorldTimerManager().SetTimer(decayTimer, this, &ABaseBuilding::DowngradeBuilding, decayTime, false);
				gruen->SetVisibility(false);
			}
		}
	}
}


ABaseBuilding::ABaseBuilding()
{
	gruen = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gruen"));
	gruen->SetupAttachment(RootComponent);
	dust = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Dust"));
	dust->SetupAttachment(RootComponent);
	pollutionComp = CreateDefaultSubobject<UPollution>(TEXT("Pollution"));
	cashComp = CreateDefaultSubobject<UCash>(TEXT("Cash"));
}
