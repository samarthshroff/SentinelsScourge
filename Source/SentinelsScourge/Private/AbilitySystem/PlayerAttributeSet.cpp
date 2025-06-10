// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/PlayerAttributeSet.h"

#include "SentinelsScourgeGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "Player/PlayerCharacterState.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	AllAttributes.Empty();
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Health, GetHealthAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_MaxHealth, GetMaxHealthAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Recovery, GetRecoveryAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Armor, GetArmorAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_MoveSpeed, GetMoveSpeedAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Might, GetMightAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Area, GetAreaAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Speed, GetSpeedAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Duration, GetDurationAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Amount, GetAmountAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Cooldown, GetCooldownAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Luck, GetLuckAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Growth, GetGrowthAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Greed, GetGreedAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Curse, GetCurseAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Magnet, GetMagnetAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Revival, GetRevivalAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Reroll, GetRerollAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Skip, GetSkipAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Banish, GetBanishAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Charm, GetCharmAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Defang, GetDefangAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Seal, GetSealAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_Level, GetLevelAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_XP, GetXPAttribute);
	AllAttributes.Add(SentinelsScourgeGameplayTags::Player_Attributes_MaxXP, GetMaxXPAttribute);
}

// void UPlayerAttributeSet::IncrementLevel(const int32 NewLevel)
// {
// 	SetLevel(NewLevel);
// 	UpdateMaxXPForLevel(NewLevel);
// 	SetXP(0.0f);
// }

void UPlayerAttributeSet::UpdateMaxXPForLevel()
{
	const int32 CurrentLevel = GetLevel();
	// TODO - This TMap will be a Data Asset later one.
	const int32 Levels[] = {1, 2, 20, 40};
	// const int32 MaxXPs[] = {5,10,13,16};
	const int32 MaxXPs[] = {2, 2, 2, 2};

	const int32 Count = UE_ARRAY_COUNT(Levels);
	int32 MaxXPPoint = -1;

	int32 Low = 0;
	int32 High = Count - 1;

	while (Low <= High)
	{
		const int32 Mid = (Low + High) / 2;
		if (Levels[Mid] <= CurrentLevel)
		{
			MaxXPPoint = MaxXPs[Mid];
			Low = Mid + 1;
			continue;
		}
		if (Levels[Mid] > CurrentLevel)
		{
			High = Mid - 1;
			continue;
		}
	}

	SetMaxXP(MaxXPPoint);
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetXPAttribute())
	{
		if (GetXP() >= GetMaxXP())
		{
			SetXP(GetMaxXP());
			SetLevel(GetLevel() + 1);
			// TODO - call these 2 functions from the response (button click) of ability selection overlay.
			// 	UpdateMaxXPForLevel(NewLevel);
			// 	SetXP(0.0f);
		}
	}
}

void UPlayerAttributeSet::UpdateXPs()
{
	UpdateMaxXPForLevel();
	SetXP(0.0f);
	UE_LOG(LogTemp, Log, TEXT("UPlayerAttributeSet::UpdateXPs the XP is:: %f and MaxXP is:: %f"), GetXP(), GetMaxXP());
}

void UPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute &Attribute, float &NewValue)
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
