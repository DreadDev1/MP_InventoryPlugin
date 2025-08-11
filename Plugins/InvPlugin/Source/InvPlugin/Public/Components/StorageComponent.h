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

protected:
	virtual void BeginPlay() override;
	
public:	
	UStorageComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int Capacity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	int SlotsFilled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<FInventoryItem> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	UDataTable* DataTable;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnStorageCompUpdated OnInventoryUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnStorageCompFull OnInventoryFull;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FInventoryItem> GetItems() { return Items; }

	bool AddItem(FInventoryItem Item);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ServerAddBPItem(FInventoryItem Item);

	bool RemoveItem(FInventoryItem Item);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ServerRemoveBPItem(FInventoryItem Item);

	bool RemoveItemStack(FName UniqueName, int StackSize);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool ServerRemoveBPItemStack(FName UniqueName, int StackSize);
	
	bool HasItem(FName UniqueName, int StackSize);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool BPHasItem(FName UniqueName, int StackSize);

	int GetFirstEmpty();
	int AddEmptyAtIndex(int Index);
	
	

	void UpdateUI();
};
