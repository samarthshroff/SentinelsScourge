// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCalc/MMC_PlayerMight.h"

#include "AbilitySystem/PlayerAttributeSet.h"
#include "Character/CharacterBaseInterface.h"

UMMC_PlayerMight::UMMC_PlayerMight()
{

}

float UMMC_PlayerMight::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	ICharacterBaseInterface* CharacterInterface = Cast<ICharacterBaseInterface>(Spec.GetContext().GetSourceObject());
	//int32 Level = CharacterInterface->GetCharacterLevel();
	//UE_LOG(LogTemp, Log, TEXT("UMMC_PlayerMight::CalculateBaseMagnitude_Implementation Level: %d"), Level);
	//Level = FMath::Clamp(Level, 1, 50);
	//int32 MightBonusPercentage = (Level/10)*10;

	int32 MightBonusPercentage = 0;
	UCurveTable* CurveTable = LoadObject<UCurveTable>(nullptr, TEXT("/Game/Blueprints/AbilitySystem/GameplayEffects/BonusAttributes/CT_BonusAttributes_Might.CT_BonusAttributes_Might"));
	if (CurveTable)
	{
		const FString FullTag = CharacterInterface->GetCharacterTag().ToString();
		FString RowName;
		FullTag.Split(TEXT("."), nullptr, &RowName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
		
		UE_LOG(LogTemp, Log, TEXT("UMMC_PlayerMight::CalculateBaseMagnitude_Implementation The RowName is: %s"), *RowName);
		FRealCurve* Curve = CurveTable->FindCurve(*RowName,
			FString::Printf(TEXT("Could not find RowName: %s in CurveTable: %s"), *RowName, TEXT("CT_BonusAttributes_Might")),
			true);

		if (Curve)
		{
			int32 Level = CharacterInterface->GetCharacterLevel();
			MightBonusPercentage = Curve->Eval(Level);
			UE_LOG(LogTemp, Log, TEXT("UMMC_PlayerMight::CalculateBaseMagnitude_Implementation Level: %d"), Level);
		}
	}
	
	int32 BaseMightPercentage = 100.0f;
	
	return BaseMightPercentage + MightBonusPercentage; 
}
