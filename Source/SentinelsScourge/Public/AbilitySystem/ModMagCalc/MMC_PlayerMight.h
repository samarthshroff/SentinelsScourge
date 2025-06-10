// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_PlayerMight.generated.h"

/**
 * MMC class that modifies the Player's Might attribute based on the selected Hero character's bonus attribute values.
 */
UCLASS()
class SENTINELSSCOURGE_API UMMC_PlayerMight : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_PlayerMight();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec &Spec) const override;
};
