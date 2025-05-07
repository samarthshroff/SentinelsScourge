// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_PlayerMight.h"

#include "AbilitySystem/PlayerAttributeSet.h"
#include "Character/CharacterBaseInterface.h"

UMMC_PlayerMight::UMMC_PlayerMight()
{

}

float UMMC_PlayerMight::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const ICharacterBaseInterface* CharacterInterface = Cast<ICharacterBaseInterface>(Spec.GetContext().GetSourceObject());

	int32 MightBonus = 0;
	// Path hard coding is not good, but I am okay for the prototype.
	const UCurveTable* CurveTable = LoadObject<UCurveTable>(nullptr, TEXT("/Game/Blueprints/AbilitySystem/GameplayEffects/Player/BonusAttributes/CT_PlayerBonus_Might.CT_PlayerBonus_Might"));
	if (CurveTable)
	{
		const FString FullTag = CharacterInterface->GetCharacterTag().ToString();
		FString RowName;
		FullTag.Split(TEXT("."), nullptr, &RowName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
				
		FRealCurve* Curve = CurveTable->FindCurve(*RowName,
			FString::Printf(TEXT("Could not find RowName: %s in CurveTable: %s"), *RowName, TEXT("CT_BonusAttributes_Might")),
			true);

		if (Curve)
		{
			MightBonus = Curve->Eval(CharacterInterface->GetCharacterLevel());		
		}
	}

	constexpr int32 BaseMight = 1.0f;
	
	return BaseMight + MightBonus; 
}
