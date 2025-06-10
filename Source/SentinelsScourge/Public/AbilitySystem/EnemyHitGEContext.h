// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once
#include "GameplayEffectTypes.h"
#include "EnemyHitGEContext.generated.h"

USTRUCT(BlueprintType)
struct FEnemyHitGEContext : public FGameplayEffectContext
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	float Knockback = 0.0f;

public:
	void SetKnockback(float Value);

	float GetKnockback() const;


	virtual UScriptStruct* GetScriptStruct() const override;
	virtual FGameplayEffectContext* Duplicate() const override;
};
