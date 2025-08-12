// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StorageComponent.h"
#include "Engine/DataTable.h"
#include "Items/Base/BaseItem.h"
#include "Net/UnrealNetwork.h"

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

void UStorageComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStorageComponent, Items);
	DOREPLIFETIME(UStorageComponent, Capacity);
	DOREPLIFETIME(UStorageComponent, SlotsFilled);
}

int UStorageComponent::GetFirstEmpty()
{
	for (FInventoryItem& a : Items)
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
	OnInventoryUpdated.Broadcast();
}

void UStorageComponent::ServerAddBPItem_Implementation(FInventoryItem Item)
{
	AddItem(Item);
}

void UStorageComponent::OnRep_StorageUpdated()
{
	OnInventoryUpdated.Broadcast();
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

void UStorageComponent::ServerRemoveBPItem_Implementation(FInventoryItem Item)
{
	RemoveItem(Item);
}

bool UStorageComponent::RemoveItemStack(FName UniqueName, int StackSize)
{
	int PendingCount = StackSize;
	
	for (FInventoryItem& a : Items)
	{
		if (a.UniqueName == UniqueName)
		{
			if (a.StackSize <= PendingCount)
			{
				PendingCount -= a.StackSize;
				RemoveItem(a);
			}
			else
			{
				a.StackSize -= PendingCount;
				PendingCount = 0;
			}
		}
		if (PendingCount == 0)
		{
			UpdateUI();
			return true;
		}
	}
	return false;
}

void UStorageComponent::ServerRemoveBPItemStack_Implementation(FName UniqueName, int StackSize)
{
	RemoveItemStack(UniqueName, StackSize);
}

bool UStorageComponent::HasItem(FName UniqueName, int StackSize)
{
	int PendingCount = StackSize;
	for (FInventoryItem& a : Items)
	{
		if (a.UniqueName == UniqueName)
		{
			PendingCount -= a.StackSize;
			if (PendingCount <= 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool UStorageComponent::BPHasItem(FName UniqueName, int StackSize)
{
	return HasItem(UniqueName, StackSize);
}

