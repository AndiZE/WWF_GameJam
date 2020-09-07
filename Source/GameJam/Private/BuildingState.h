#pragma once
#include "CoreMinimal.h"

UENUM()
enum class EBuildingState : uint8 {
	Green,
	Dirty,
	Abbandoned
};