// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VampireSurvivorPlayerState.h"

#include "AbilitySystem/VSAbilitySystemComponent.h"
#include "AbilitySystem/VSPlayerAttributeSet.h"

AVampireSurvivorPlayerState::AVampireSurvivorPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UVSAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(false);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);	
	AttributeSet = CreateDefaultSubobject<UVSPlayerAttributeSet>("AttributeSet");	
}

UAbilitySystemComponent* AVampireSurvivorPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AVampireSurvivorPlayerState::GetAttributeSetComponent() const
{
	return AttributeSet;
}

void AVampireSurvivorPlayerState::BeginPlay()
{
	Super::BeginPlay();

	Cast<UVSPlayerAttributeSet>(AttributeSet)->Initialize();
}
