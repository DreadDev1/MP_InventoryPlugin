#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StorageComponent.h"

#include "SharedStorage.generated.h"

class UStorageComponent;
UCLASS()
class INVPLUGIN_API ASharedStorage : public AActor
{
      GENERATED_BODY()
public:
	ASharedStorage(const FObjectInitializer& ObjectInitializer);
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "Inventory")
	UStorageComponent* StorageComponent;
	
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory")
	void ServerAddBPItem(FInventoryItem Item);
	
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory")
	void ServerRemoveBPItem(FInventoryItem Item);
	
	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory")
	void ServerRemoveBPItemStack(FName UniqueName, int StackSize);
	
protected:
	virtual void BeginPlay() override;

	
	
 
};