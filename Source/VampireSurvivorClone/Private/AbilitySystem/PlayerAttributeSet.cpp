// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PlayerAttributeSet.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameplayEffectExtension.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	
}

// void UPlayerAttributeSet::Initialize()
// {
// 	const FString Path = "/Game/AttributesDTs/DT_PlayerAttributes.DT_PlayerAttributes";
// 	TSoftObjectPtr<UDataTable> CurrentDataTable = TSoftObjectPtr<UDataTable>(FSoftObjectPath (Path));
//
// 	FStreamableManager& Manager = UAssetManager::GetStreamableManager();
// 	UObject* DataTable = Manager.LoadSynchronous(CurrentDataTable.ToSoftObjectPath());
//
// 	if (UDataTable* LoadedDataTable = Cast<UDataTable>(DataTable))
// 	{
// 		InitFromMetaDataTable(LoadedDataTable);
// 	}	
// }

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
		NewValue = FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth());
	}
}

// float UPlayerAttributeSet::GetHealth() const
// {
// 	// Return Health's current value, but never return a value lower than zero.
// 	// This is the value after all modifiers that affect Health have been considered.
// 	return FMath::Max(Health.GetCurrentValue(), 0.0f);
// }
//  
// void UPlayerAttributeSet::SetHealth(float NewHealth) const
// {
// 	// Do not accept values lower than zero.
// 	NewHealth = FMath::Max(NewHealth, 0.0f);
//  
// 	// Make sure we have an Ability System Component instance. This should always be the case.
// 	UAbilitySystemComponent* Asc = GetOwningAbilitySystemComponent();
// 	if (ensure(Asc))
// 	{
// 		// Set the base value (not the current value) through the appropriate function.
// 		// This makes sure that any modifiers we have applied will still work properly.
// 		Asc->SetNumericAttributeBase(GetHealthAttribute(), NewHealth);
// 	}
// }

// FGameplayAttribute UPlayerAttributeSet::GetMaxHealthAttribute()
// {
// 	static FProperty* Prop = FindFieldChecked<FProperty>(UPlayerAttributeSet::StaticClass(),
// 														 ((void)sizeof(UEAsserts_Private::GetMemberNameCheckedJunk(
// 															 ((UPlayerAttributeSet*)0)->MaxHealth)), FName(
// 															 L"MaxHealth")));
// 	return Prop;
// }
//
// float UPlayerAttributeSet::GetMaxHealth() const { return MaxHealth.GetCurrentValue(); }
//
// void UPlayerAttributeSet::SetMaxHealth(float NewVal)
// {
// 	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
// 	if (((!!(!!(AbilityComp))) || (::UE::Assert::Private::ExecCheckImplInternal(
// 			[]() __declspec(noinline) __declspec(code_seg(".uedbg")) -> std::atomic<bool>& {
// 				static std::atomic<bool> ENSURE_bExecuted = false;
// 				return ENSURE_bExecuted;
// 			}(), false, "VSPlayerAttributeSet. h", 129, "AbilityComp") && []()
// 		{
// 			(__nop(), __debugbreak());
// 			return false;
// 		}()))) { AbilityComp->SetNumericAttributeBase(GetMaxHealthAttribute(), NewVal); };
// }
//
// void UPlayerAttributeSet::InitMaxHealth(float NewVal)
// {
// 	NewVal = ( 100 + character bonus ) * PowerUp multiplier
// 	MaxHealth.SetBaseValue(NewVal);
// 	MaxHealth.SetCurrentValue(NewVal);
// };
