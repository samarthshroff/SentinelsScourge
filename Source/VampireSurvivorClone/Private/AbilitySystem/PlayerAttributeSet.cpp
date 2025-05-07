// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PlayerAttributeSet.h"

#include "VampireSurvivorGameplayTags.h"
#include "GameplayEffectExtension.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	AllAttributes.Empty();
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Health, GetHealthAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_MaxHealth, GetMaxHealthAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Recovery, GetRecoveryAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Armor, GetArmorAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_MoveSpeed, GetMoveSpeedAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Might, GetMightAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Area, GetAreaAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Speed, GetSpeedAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Duration, GetDurationAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Amount, GetAmountAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Cooldown, GetCooldownAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Luck, GetLuckAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Growth, GetGrowthAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Greed, GetGreedAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Curse, GetCurseAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Magnet, GetMagnetAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Revival, GetRevivalAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Reroll, GetRerollAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Skip, GetSkipAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Banish, GetBanishAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Charm, GetCharmAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Defang, GetDefangAttribute);
	AllAttributes.Add(VampireSurvivorGameplayTags::Player_Attributes_Seal, GetSealAttribute);
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
}

void UPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
}

// TODO - UNCOMMENT THIS TO RESUME ADDING MULTIPLAYER SUPPORT.
/*void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Recovery, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Might, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Area, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Speed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Duration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Amount, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Cooldown, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Luck, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Growth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Greed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Curse, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Magnet, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Revival, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Reroll, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Skip, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Banish, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Charm, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Defang, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Seal, COND_None, REPNOTIFY_Always);
}

void UPlayerAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Health, OldValue);
}

void UPlayerAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MaxHealth, OldValue);
}

void UPlayerAttributeSet::OnRep_Recovery(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Recovery, OldValue);
}

void UPlayerAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Armor, OldValue);
}

void UPlayerAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MoveSpeed, OldValue);
}

void UPlayerAttributeSet::OnRep_Might(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Might, OldValue);
}

void UPlayerAttributeSet::OnRep_Area(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Area, OldValue);
}

void UPlayerAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Speed, OldValue);
}

void UPlayerAttributeSet::OnRep_Duration(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Duration, OldValue);
}

void UPlayerAttributeSet::OnRep_Amount(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Amount, OldValue);
}

void UPlayerAttributeSet::OnRep_Cooldown(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Cooldown, OldValue);
}

void UPlayerAttributeSet::OnRep_Luck(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Luck, OldValue);
}

void UPlayerAttributeSet::OnRep_Growth(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Growth, OldValue);
}

void UPlayerAttributeSet::OnRep_Greed(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Greed, OldValue);
}

void UPlayerAttributeSet::OnRep_Curse(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Curse, OldValue);
}

void UPlayerAttributeSet::OnRep_Magnet(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Magnet, OldValue);
}

void UPlayerAttributeSet::OnRep_Revival(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Revival, OldValue);
}

void UPlayerAttributeSet::OnRep_Reroll(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Reroll, OldValue);
}

void UPlayerAttributeSet::OnRep_Skip(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Skip, OldValue);
}

void UPlayerAttributeSet::OnRep_Banish(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Banish, OldValue);
}

void UPlayerAttributeSet::OnRep_Charm(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Charm, OldValue);
}

void UPlayerAttributeSet::OnRep_Defang(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Defang, OldValue);
}

void UPlayerAttributeSet::OnRep_Seal(const FGameplayAttributeData& OldValue) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Seal, OldValue);
}*/
