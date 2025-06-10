// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerState.h"
#include "PlayerCharacterState.generated.h"

class UHeroAbilitySystemComponent;
class UAttributeSet;

// DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerLevelChangedDelegate, int32)

/**
 * Mainly used for multiplayer setup. I may remove this if I don't plan on making this project multiplayer or if
 there is not other functionality introduced (am thinking level).
 * If I do make it multiplayer, then I will have to set the replication mode in cpp to mixed/minimal for self and others accordingly.
 */
UCLASS()
class SENTINELSSCOURGE_API APlayerCharacterState : public APlayerState //, public IAbilitySystemInterface
{
	GENERATED_BODY()
protected:
	UPROPERTY() // EditDefaultsOnly, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComp;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere)
	FGameplayTag CurrentHeroTag;

public:
	APlayerCharacterState();

	UAbilitySystemComponent *GetAbilitySystemComponent() const;
	UAttributeSet *GetAttributeSetComponent() const;

	// FPlayerLevelChangedDelegate PlayerLevelChanged;

	int32 GetCurrentLevel() const;

	void SetCurrentLevel(int32 NewLevel);

	FGameplayTag GetCurrentHeroTag() const;

	void Initialize();

protected:
	virtual void BeginPlay() override;

	// private:
	// 	void UpdateMaxXPForLevel(const int InLevel);
};
