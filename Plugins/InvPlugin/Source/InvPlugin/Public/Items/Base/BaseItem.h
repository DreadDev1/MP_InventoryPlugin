#pragma once

#include "CoreMinimal.h"

#include "Engine/DataTable.h"

#include "BaseItem.generated.h"

class UTexture2D;
class UStaticMesh;
class USkeletalMesh;

UENUM(BlueprintType, Category = "Inventory")
enum eItemType
{
	Unset		UMETA(DisplayName = "Unset"),
	Weapon		UMETA(DisplayName = "Weapon"),
	Spell		UMETA(DisplayName = "Spell"),
	Food		UMETA(DisplayName = "Food"),
	Potion		UMETA(DisplayName = "Potion"),
	Armor		UMETA(DisplayName = "Armor"),
	Material	UMETA(DisplayName = "Material")	
};

USTRUCT(BlueprintType, Category = "Inventory")
struct FItemRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TEnumAsByte<eItemType> ItemType = eItemType::Unset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FName UniqueName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FText ItemDisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FText UseActionText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UTexture2D* ItemIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UStaticMesh* STItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	USkeletalMesh* SKItemMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (ClampMin = "1.0"))
	int StackSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (ClampMin = "1.0", ClampMax = "99.0"))
	int MaxStackSize = 99;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (ClampMin = "1.0", ClampMax = "1000.0"))
	float Cost = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (ClampMin = "1.0", ClampMax = "1000.0"))
	float SellCost = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bIsSopItem = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (ClampMin = "1.0", ClampMax = "1000.0"))
	FString CostType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bIsConsumable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bIsStackable = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bHasMaxStackSize = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bIsRare = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bIsBound = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bIsEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bIsAltEnabled = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bHasCooldown = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (ClampMin = "1.0", ClampMax = "60.0") )
	float CooldownTime = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (ClampMin = "1.0", ClampMax = "60.0") )
	float AltCooldownTime = 10.f;
};