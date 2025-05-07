// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerState.h"
#include "PlayerCharacterState.generated.h"

class UVSAbilitySystemComponent;
class UAttributeSet;

DECLARE_MULTICAST_DELEGATE_OneParam(FPlayerLevelChangedDelegate, int32)

/**
 * Mainly used for multiplayer setup. I may remove this if I don't plan on making this project multiplayer or if 
 there is not other functionality introduced (am thinking level).
 * If I do make it multiplayer, then I will have to set the replication mode in cpp to mixed/minimal for self and others accordingly. 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API APlayerCharacterState : public APlayerState//, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerCharacterState();

	UAbilitySystemComponent* GetAbilitySystemComponent() const;
	UAttributeSet* GetAttributeSetComponent() const;

	FPlayerLevelChangedDelegate PlayerLevelChanged;

	int32 GetCurrentLevel() const;

	void SetCurrentLevel(int32 NewLevel);

	FGameplayTag GetCurrentHeroTag() const;

	void Initialize();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere)
	FGameplayTag CurrentHeroTag;
};
