// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterState.h"
#include "VampireSurvivorGameplayTags.h"
#include "AbilitySystem/HeroAbilitySystemComponent.h"
#include "AbilitySystem/PlayerAttributeSet.h"

APlayerCharacterState::APlayerCharacterState()
{
	AbilitySystemComp = CreateDefaultSubobject<UHeroAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComp->SetIsReplicated(false);
	// TODO - replace Full with Mixed WHEN ADDING MULTIPLAYER SUPPORT.
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Full); 	
	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* APlayerCharacterState::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

UAttributeSet* APlayerCharacterState::GetAttributeSetComponent() const
{
	return AttributeSet;
}

int32 APlayerCharacterState::GetCurrentLevel() const
{
	return Level;
}

void APlayerCharacterState::SetCurrentLevel(int32 NewLevel)
{
	Level = NewLevel;
	PlayerLevelChanged.Broadcast(Level);
}

FGameplayTag APlayerCharacterState::GetCurrentHeroTag() const
{
	return CurrentHeroTag;
}

void APlayerCharacterState::Initialize()
{
	CurrentHeroTag = VampireSurvivorGameplayTags::Hero_Antonio;
	SetCurrentLevel(1);
	UE_LOG(LogTemp, Log, TEXT("APlayerCharacterState::Initialize Level: %d"), Level);
}

void APlayerCharacterState::BeginPlay()
{
	Super::BeginPlay();
	PlayerLevelChanged.Broadcast(Level);
	//Cast<UPlayerAttributeSet>(AttributeSet)->Initialize();
}
