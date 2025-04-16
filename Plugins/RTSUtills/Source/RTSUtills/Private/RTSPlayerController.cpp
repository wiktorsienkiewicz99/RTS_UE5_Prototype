// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"

ARTSPlayerController::ARTSPlayerController()
{
	bShowMouseCursor = true;
}

/**
 * Overrides the SetupInputComponent function to initialize input mappings
 * for the RTS player controller.
 *
 * This method checks if a default input mapping context is provided.
 * If available, it retrieves the UEnhancedInputLocalPlayerSubsystem associated with the local player
 * and adds the DefaultInputMappingContext to the input subsystem for the player.
 * An additional log entry is output to confirm the addition of the input mapping context.
 *
 * If no DefaultInputMappingContext is provided, the method exits early without performing any setup.
 */
void ARTSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!DefaultInputMappingContext)
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		LocalPlayerSubsystem->AddMappingContext(DefaultInputMappingContext, 0);
		UE_LOG(LogTemp, Display, TEXT("Input Mapping context added"))
	}
}
