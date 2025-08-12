// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Player/InventoryPC.h"
#include "MP_InventoryPluginPlayerController.generated.h"

class UStorageComponent;
class UInputMappingContext;
struct FInventoryItem;

/**
 *  Simple first person Player Controller
 *  Manages the input mapping context.
 *  Overrides the Player Camera Manager class.
 */
UCLASS(abstract)
class MP_INVENTORYPLUGIN_API AMP_InventoryPluginPlayerController : public AInventoryPC
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	AMP_InventoryPluginPlayerController();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory")
	void ServerAddBPItem(UStorageComponent* Storage, FInventoryItem Item);

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Inventory")
	void ServerRemoveBPItem(UStorageComponent* Storage, FInventoryItem Item);
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input", meta = (AllowPrivateAccess = "true"))
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

};
