// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Delegates/DelegateCombinations.h"
#include "Items/Base/InventoryItem.h"
#include "StorageComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStorageCompUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStorageCompFull);

class UDataTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVPLUGIN_API UStorageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStorageComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int Capacity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int SlotsFilled;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FInventoryItem> Items;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UDataTable* ItemTable;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnStorageCompUpdated OnInventoryUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnStorageCompFull OnInventoryFull;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FInventoryItem> GetItems() { return Items; }

	
	
	
protected:
	virtual void BeginPlay() override;



		
};
