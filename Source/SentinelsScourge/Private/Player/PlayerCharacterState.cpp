// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "Player/PlayerCharacterState.h"
#include "SentinelsScourgeGameplayTags.h"
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

UAbilitySystemComponent *APlayerCharacterState::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

UAttributeSet *APlayerCharacterState::GetAttributeSetComponent() const
{
	return AttributeSet;
}

int32 APlayerCharacterState::GetCurrentLevel() const
{
	return Cast<UPlayerAttributeSet>(AttributeSet)->GetLevel();
}

void APlayerCharacterState::SetCurrentLevel(const int32 NewLevel)
{
	Cast<UPlayerAttributeSet>(AttributeSet)->SetLevel(NewLevel);
}

FGameplayTag APlayerCharacterState::GetCurrentHeroTag() const
{
	return CurrentHeroTag;
}

void APlayerCharacterState::Initialize()
{
	AbilitySystemComp->AddLooseGameplayTag(SentinelsScourgeGameplayTags::Hero_Root);

	CurrentHeroTag = SentinelsScourgeGameplayTags::Hero_Antonio;
	SetCurrentLevel(1);
	UE_LOG(LogTemp, Log, TEXT("APlayerCharacterState::Initialize Level: %d"), GetCurrentLevel());
}

void APlayerCharacterState::BeginPlay()
{
	Super::BeginPlay();
	// PlayerLevelChanged.Broadcast(GetCurrentLevel());
}

// void APlayerCharacterState::UpdateMaxXPForLevel(const int InLevel)
// {
// 	// TODO - This TMap will be a Data Asset later one.
// 	const int32 Levels[]  = {1,2,20,40};
// 	const int32 MaxXPs[] = {5,10,13,16};
//
// 	const int32 Count = UE_ARRAY_COUNT(Levels);
// 	int32 MaxXPPoint = -1;
//
// 	int32 Low = 0;
// 	int32 High = Count - 1;
//
// 	while (Low <= High)
// 	{
// 		const int32 Mid = (Low + High) / 2;
// 		if (Levels[Mid] <= InLevel)
// 		{
// 			MaxXPPoint = MaxXPs[Mid];
// 			Low = Mid + 1;
// 			continue;
// 		}
// 		if (Levels[Mid] > InLevel)
// 		{
// 			High = Mid - 1;
// 			continue;
// 		}
// 	}
//
// 	Cast<UPlayerAttributeSet>(AttributeSet)->SetMaxXP(MaxXPPoint);
// }
