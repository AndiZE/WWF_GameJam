// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "MapCreator.h"
#include "DebugUI.h"
#include "GameFramework/SpringArmComponent.h"
#include "CineCameraComponent.h"
#include "CustomGameInstance.h"
#include "InfoScreen.h"
#include "Runtime/UMG/Public/UMG.h"
#include "LoseCash.h"
#include "Slate.h"
#include "Tile.h"

// Sets default values
ADebugPlayer::ADebugPlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	rootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = rootSceneComponent;

	//Spring Arm
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(RootComponent);

	springArm->SetRelativeRotation(FQuat(FRotator(-35.0f, 0.0f, 0.0f)));
	springArm->TargetArmLength = 2000.0f;
	springArm->bDoCollisionTest = false;

	//Camera
	cineCam = CreateDefaultSubobject<UCineCameraComponent>(TEXT("CineCamera"));
	cineCam->SetupAttachment(springArm);

	cameraSpeed = 1000.0f;
	cameraZoomMin = 700.0f;
	cameraZoomMax = 3000.0f;
	cameraZoomStep = 100.0f;
}

// Called when the game starts or when spawned
void ADebugPlayer::BeginPlay()
{
	Super::BeginPlay();
	AActor* actor = UGameplayStatics::GetActorOfClass(GetWorld(), AMapCreator::StaticClass());
	AMapCreator* castMap = Cast<AMapCreator>(actor);
	if (castMap != nullptr)
	{
		map = castMap;
	}
	if (isDebug) {
		UUserWidget* ui = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), UDebugUI::StaticClass());
		debugUI = Cast<UDebugUI>(ui);
		debugUI->AddToViewport();
	}
	else {
		UUserWidget* ui = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), UInfoScreen::StaticClass());
		infoHud = Cast<UInfoScreen>(ui);
		infoHud->AddToViewport();
		AddCash(startMoney);
		infoHud->UpdateInfo(nullptr);
	}
	player = UGameplayStatics::GetPlayerController(GetWorld(), 0);

}

// Called every frame
void ADebugPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isDebug && player)
	{
		FHitResult* hit = nullptr;
		player->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, *hit);
		int x = 0;
		int y = 0;
		if (hit != nullptr)
		{
			map->GetTilePositionFromWorldPosition(hit->Location, x, y);
			debugUI->UpdateGridText(x, y, map->GetTileFromGrid(x, y));
		}
	}

}

// Called to bind functionality to input
void ADebugPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Horizontal", this, &ADebugPlayer::MoveHorizontal);
	PlayerInputComponent->BindAxis("Vertical", this, &ADebugPlayer::MoveVertical);
	PlayerInputComponent->BindAction("Deselect", EInputEvent::IE_Pressed, this, &ADebugPlayer::DeselectTile);
	PlayerInputComponent->BindKey(EKeys::MouseScrollUp, EInputEvent::IE_Pressed, this, &ADebugPlayer::ZoomInCamera);
	PlayerInputComponent->BindKey(EKeys::MouseScrollDown, EInputEvent::IE_Pressed, this, &ADebugPlayer::ZoomOutCamera);
}

void ADebugPlayer::MoveHorizontal(float AxisValue)
{
	ADebugPlayer::AddMovement(FVector(AxisValue, 0.0f, 0.0f));
}

void ADebugPlayer::MoveVertical(float AxisValue)
{
	ADebugPlayer::AddMovement(FVector(0.0f, AxisValue, 0.0f));
}

void ADebugPlayer::AddCash(int Cash)
{
	playerCash += Cash;
	infoHud->UpdateCash(playerCash);
	SelectTile(currentSelectedTile);
	if (playerCash < 0)
	{
		UUserWidget* widget = CreateWidget(CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), ULoseCash::StaticClass()));
		widget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void ADebugPlayer::SelectTile(UTile* Tile)
{
	if (currentSelectedTile)
	{
		currentSelectedTile->GetBuilding()->GetStaticMeshComponent()->SetScalarParameterValueOnMaterials("Selection", 0.0f);
	}
	if (Tile)
	{
		currentSelectedTile = Tile;
		infoHud->UpdateInfo(currentSelectedTile);
	}
}

void ADebugPlayer::DeselectTile()
{
	if (currentSelectedTile != nullptr)
	{
		currentSelectedTile->GetBuilding()->GetStaticMeshComponent()->SetScalarParameterValueOnMaterials("Selection", 0.0f);
	}
	currentSelectedTile = nullptr;
	infoHud->UpdateInfo(currentSelectedTile);

	if (currentSelectedTile != nullptr)
	{
		currentSelectedTile->GetBuilding()->GetStaticMeshComponent()->SetScalarParameterValueOnMaterials("Selection", 1.0f);
	}

}

bool ADebugPlayer::CanSpendCash(int Cost)
{
	if (playerCash < Cost) {
		return false;
	}
	else {
		playerCash -= Cost;
		infoHud->UpdateCash(playerCash);
		return true;
	}
}

void ADebugPlayer::AddMovement(FVector Input)
{
	FVector forward = FVector(GetActorForwardVector() * Input.X * GetWorld()->GetDeltaSeconds() * cameraSpeed);
	FVector side = FVector(GetActorRightVector() * Input.Y * GetWorld()->GetDeltaSeconds() * cameraSpeed);

	FVector pos = GetActorLocation() + side + forward;

	gameInstance = Cast<UCustomGameInstance>(GetGameInstance());
	if (gameInstance == nullptr)
		return;



	SetActorLocation(FVector(FMath::Clamp(pos.X, gameInstance->camMinPos.X, gameInstance->camMaxPos.X),
		FMath::Clamp(pos.Y, gameInstance->camMinPos.Y, gameInstance->camMaxPos.Y),
		pos.Z));
}

void ADebugPlayer::ZoomInCamera()
{
	springArm->TargetArmLength = FMath::Clamp(springArm->TargetArmLength - cameraZoomStep, cameraZoomMin, cameraZoomMax);
}

void ADebugPlayer::ZoomOutCamera()
{
	springArm->TargetArmLength = FMath::Clamp(springArm->TargetArmLength + cameraZoomStep, cameraZoomMin, cameraZoomMax);
}

