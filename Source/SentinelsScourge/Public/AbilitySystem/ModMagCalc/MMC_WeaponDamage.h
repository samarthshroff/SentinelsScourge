// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_WeaponDamage.generated.h"

/**
 * MMC class to modify the Damage Attribute of a weapon based on Player's might attribute
 */
UCLASS()
class SENTINELSSCOURGE_API UMMC_WeaponDamage : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_WeaponDamage();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec &Spec) const override;
};
