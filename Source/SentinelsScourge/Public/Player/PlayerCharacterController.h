// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

class USplineComponent;
struct FInputActionValue;

/**
 *
 */
UCLASS()
class SENTINELSSCOURGE_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

private:
	// The last mouse clicked location
	FVector ClickedLocation = FVector::Zero();
	// The total amount of seconds the mouse button was held.
	float FollowTime = 0.0f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.0f;

	// For moving (auto run) the character along a path towards (around obstacles if any) the mouse click.
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

public:
	void AutoRun();
	virtual void Tick(float DeltaSeconds) override;

	APlayerCharacterController();
	void MoveButtonHeld(const FInputActionValue &Value);
	void MoveButtonPressed(const FInputActionValue &Value);
	void MoveButtonReleased(const FInputActionValue &Value);
};
