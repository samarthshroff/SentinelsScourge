// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "BaseUnlockCondition.h"
#include "KillEnemiesCondition.generated.h"

/**
 *
 */
UCLASS()
class SENTINELSSCOURGE_API UKillEnemiesCondition : public UBaseUnlockCondition
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kill Condition")
	int32 EnemiesToKill;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Kill Condition")
	int32 CurrentKills;

	// Specific enemy type to kill. If Enemy root tag specified then all enemies will be considered.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kill Condition")
	FGameplayTag TargetEnemyClass;

	virtual void InitializeCondition(AActor *OwningActor) override; // Hook to GameState/PlayerState events
	void OnEnemyKilled(int32 Kills);								// Listener function for game event
};
