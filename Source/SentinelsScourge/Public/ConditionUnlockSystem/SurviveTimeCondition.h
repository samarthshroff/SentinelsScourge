// Fill out your copyright notice in the Description page of Project Settings.

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
