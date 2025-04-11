// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_PlayerMight.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UMMC_PlayerMight : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_PlayerMight();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

// private:
// 	FGameplayEffectAttributeCaptureDefinition MightDef;
};
