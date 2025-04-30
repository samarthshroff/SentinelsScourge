// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VSGameplayAbility.h"
#include "VSProjectileDirect.generated.h"

class AVSProjectile;
/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UVSProjectileDirect : public UVSGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AVSProjectile> ProjectileClass;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
public:
	UVSProjectileDirect();
};
