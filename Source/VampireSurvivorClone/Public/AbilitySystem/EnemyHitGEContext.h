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
