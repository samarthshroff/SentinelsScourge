// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterState.h"

#include "AbilitySystem/VSAbilitySystemComponent.h"
#include "AbilitySystem/PlayerAttributeSet.h"

APlayerCharacterState::APlayerCharacterState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UVSAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(false);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);	
	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* APlayerCharacterState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* APlayerCharacterState::GetAttributeSetComponent() const
{
	return AttributeSet;
}

void APlayerCharacterState::BeginPlay()
{
	Super::BeginPlay();

	//Cast<UPlayerAttributeSet>(AttributeSet)->Initialize();
}
