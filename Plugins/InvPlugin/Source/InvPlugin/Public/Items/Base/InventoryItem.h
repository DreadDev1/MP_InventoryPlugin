#pragma once

#include "CoreMinimal.h"

#include "InventoryItem.generated.h"

USTRUCT(BlueprintType, Category = "Inventory")
struct FInventoryItem 
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FName UniqueName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (ClampMin = 1.0))
	int StackSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int Index = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bIsEmpty = false;

	bool operator == (const FInventoryItem rhs) const { return UniqueName == rhs.UniqueName; }
};