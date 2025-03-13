// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

struct FInputActionValue;
/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerCharacterController();

	void ClickTriggered(const FInputActionValue& Value);
	//void ClickStarted(const FInputActionValue& Value);
	// void ClickCanceled(const FInputActionValue& Value);
	// void ClickCompleted(const FInputActionValue& Value);
};
