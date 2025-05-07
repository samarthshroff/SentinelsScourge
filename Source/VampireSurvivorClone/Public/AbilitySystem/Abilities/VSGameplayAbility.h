// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VSGameplayAbilityInterface.h"
#include "Abilities/GameplayAbility.h"
#include "VSGameplayAbility.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityCooldownComplete, const FActiveGameplayEffect* ActiveGameplayEffect)

/**
 * The base class for all abilities of this project.
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UVSGameplayAbility : public UGameplayAbility, public IVSGameplayAbilityInterface
{
	GENERATED_BODY()

public:
	virtual void Initialize(float InCooldown) override;

	static FOnAbilityCooldownComplete OnAbilityCooldownCompleteDelegate;
};
