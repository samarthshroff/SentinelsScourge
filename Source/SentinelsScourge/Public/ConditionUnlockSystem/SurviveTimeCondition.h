// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "BaseUnlockCondition.h"
#include "SurviveTimeCondition.generated.h"

/**
 *
 */
UCLASS()
class SENTINELSSCOURGE_API USurviveTimeCondition : public UBaseUnlockCondition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Condition")
	float TimeToSurviveSeconds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Time Condition")
	float CurrentSurvivedTime;

	virtual void InitializeCondition(AActor *OwningActor) override;
	void OnGameTimerUpdate(float ElapsedTime); // Listener function for game timer event
};
