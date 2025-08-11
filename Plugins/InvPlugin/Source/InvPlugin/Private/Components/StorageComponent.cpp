// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StorageComponent.h"
#include "Engine/DataTable.h"
#include "Items/Base/BaseItem.h"

// Sets default values for this component's properties
UStorageComponent::UStorageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStorageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStorageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UStorageComponent::GetFirstEmpty()
{
	for (FInventoryItem a : Items)
	{
		if (a.bIsEmpty)
		{
			return a.Index;
		}
	}
	return -1;
}

int UStorageComponent::AddEmptyAtIndex(int Index)
{
	FInventoryItem EmptyItem = FInventoryItem();
	EmptyItem.Index = Index;
	EmptyItem.bIsEmpty = true;
	EmptyItem.ItemOwner = this;
	Items.Insert(EmptyItem, Index);
	UpdateUI();
	return Index;
}

void UStorageComponent::UpdateUI()
{
}

void UStorageComponent::ServerAddBPItem(FInventoryItem Item)
{
	AddItem(Item);
}

bool UStorageComponent::AddItem(FInventoryItem Item)
{
	if (SlotsFilled >= Capacity)
	{
		OnInventoryFull.Broadcast();
		return false;
	}

	// process if Item Is Stackable
	if (DataTable)
	{
		FItemRow* ItemRow = DataTable->FindRow<FItemRow>(Item.UniqueName, "");

		int PendingStackSize = Item.StackSize;

		if (ItemRow->bIsStackable)
		{
			for (FInventoryItem& a : Items)
			{
				if (a == Item)
				{
					if (!ItemRow->bHasMaxStackSize)
					{
						a.StackSize += PendingStackSize;
						UpdateUI();
						return true;
					}
					else
					{
						if (a.StackSize < ItemRow->MaxStackSize)
						{
							int OldStackSize = a.StackSize;

							// Overflows max stack size, we want to max out the stack size
							//and subtract from the pending stack size and continue
							if ((OldStackSize + PendingStackSize) > ItemRow->MaxStackSize)
							{
								int Diff = (OldStackSize + PendingStackSize) - ItemRow->MaxStackSize;
								a.StackSize = ItemRow->MaxStackSize;
								PendingStackSize = Diff;
							}
							else
							{
								a.StackSize += PendingStackSize;
								PendingStackSize = 0;
							}
						}
					}
				}

				if (PendingStackSize == 0)
				{
					UpdateUI();
					return true;
				}
			}
		}

		int NewIndex = GetFirstEmpty();
		Items.RemoveAt(NewIndex);
	
		Item.Index = NewIndex;
		Item.StackSize = PendingStackSize;
		Item.ItemOwner = this;

		Items.Insert(Item, NewIndex);
		SlotsFilled++;

		UpdateUI();
		return true;
	}
	
	return false;
}

void UStorageComponent::ServerRemoveBPItem(FInventoryItem Item)
{
	RemoveItem(Item);
}

bool UStorageComponent::RemoveItem(FInventoryItem Item)
{
	int Index = Item.Index;
	if (Index >= -1)
	{
		Items.RemoveAt(Index);
		AddEmptyAtIndex(Index);
		SlotsFilled--;
		UpdateUI();
		return true;
	}
	return false;
}

