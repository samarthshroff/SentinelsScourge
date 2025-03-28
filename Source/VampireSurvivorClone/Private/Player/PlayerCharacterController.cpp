// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireSurvivorClone/Public/Player/PlayerCharacterController.h"

#include "AbilitySystemComponent.h"
#include "Player/PlayerCharacter.h"
#include "Player/VampireSurvivorPlayerState.h"

APlayerCharacterController::APlayerCharacterController()
{
	bShowMouseCursor = true;
}

void APlayerCharacterController::ClickTriggered(const FInputActionValue& Value)
{
	FHitResult Result;

	// Move the player in the world to the mouse click location on screen
	// Get the world position of the mouse click.
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, Result);
	if (Result.bBlockingHit)
	{
		FVector DirectionVector = Result.Location - GetPawn()->GetActorLocation();
		DirectionVector.Z = 0.0f;
		if (!DirectionVector.IsNearlyZero())
		{
			GetPawn()->AddMovementInput(DirectionVector);
			FRotator SmoothRotation = FMath::RInterpTo(GetPawn()->GetActorRotation(), DirectionVector.Rotation(), GetWorld()->GetDeltaSeconds(), 10.0f);
			GetPawn()->SetActorRotation(DirectionVector.Rotation());	
		}		
	}	
}
