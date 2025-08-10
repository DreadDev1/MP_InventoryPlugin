// Copyright Epic Games, Inc. All Rights Reserved.



#include "Public/Player/MP_InventoryPluginPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Public/Character/Camera/MP_InventoryPluginCameraManager.h"


AMP_InventoryPluginPlayerController::AMP_InventoryPluginPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AMP_InventoryPluginCameraManager::StaticClass();
}

void AMP_InventoryPluginPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
