// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "SSGameplayAbilityInterface.h"
#include "Abilities/GameplayAbility.h"
#include "SSGameplayAbility.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityCooldownComplete, const FActiveGameplayEffect *ActiveGameplayEffect)

/**
 * The base class for all abilities of this project.
 */
UCLASS() class SENTINELSSCOURGE_API USSGameplayAbility : public UGameplayAbility, public ISSGameplayAbilityInterface
{
	GENERATED_BODY()

public:
	virtual void Initialize(float InCooldown) override;

	static FOnAbilityCooldownComplete OnAbilityCooldownCompleteDelegate;
};
