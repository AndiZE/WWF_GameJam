#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TileDirection.generated.h"

UENUM()
enum class ETileDirection : uint8 {
	North,
	East,
	South,
	West
};

UCLASS()
class UTileDirectionExtension : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
		static ETileDirection GetOpposite(ETileDirection Direction);
};