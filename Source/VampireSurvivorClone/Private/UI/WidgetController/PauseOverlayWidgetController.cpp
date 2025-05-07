// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/PauseOverlayWidgetController.h"

#include "AbilitySystem/PlayerAttributeSet.h"
#include "Kismet/GameplayStatics.h"

void UPauseOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();

	for (TTuple<FGameplayTag, FGameplayAttribute(*)()>& Elem : GetPlayerAttributeSet()->AllAttributes)
	{
		FGameplayAttribute Attribute = Elem.Value();
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UPauseOverlayWidgetController::AttributeChanged);
	}
}

void UPauseOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	
	for (TTuple<FGameplayTag, FGameplayAttribute(*)()>& Elem : GetPlayerAttributeSet()->AllAttributes)
	{
		FGameplayAttribute Attribute = Elem.Value();
		if (Attribute == GetPlayerAttributeSet()->GetHealthAttribute()) continue;
		FString Name;
		FString ValueStr;
		GetAttributeNameAndValue(Attribute, Attribute.GetNumericValue(PlayerAttributeSet), Name, ValueStr);
		//UE_LOG(LogTemp, Log, TEXT("UPauseOverlayWidgetController::BroadcastInitialValues Name: %s Value: %s"), *Name, *ValueStr);
		OnPlayerAttributeValueChanged.Broadcast(Name, ValueStr, Elem.Key);
	}
}

void UPauseOverlayWidgetController::OnResumeButtonClicked()
{
	UGameplayStatics::SetGamePaused(GetWorld(),false);
}

void UPauseOverlayWidgetController::GetAttributeNameAndValue(const FGameplayAttribute& Attribute, const float ValueFloat,
															 FString& Name, FString& ValueStr) const
{
	// UE_LOG(LogTemp, Log, TEXT("UPauseOverlayWidgetController::GetAttributeNameAndValue The Attribute name %s and attribute value is:: %f "), 
	//        *(Attribute.GetName()),(ValueFloat));

	Name = Attribute.AttributeName;
	int ValueInt = static_cast<int>(ValueFloat);
	ValueStr = FString::Printf(TEXT("%d"), ValueInt);

	if (Attribute == UPlayerAttributeSet::GetMightAttribute() ||
		Attribute == UPlayerAttributeSet::GetMoveSpeedAttribute() ||		
		Attribute == UPlayerAttributeSet::GetSpeedAttribute() ||
		Attribute == UPlayerAttributeSet::GetDurationAttribute() ||
		Attribute == UPlayerAttributeSet::GetAreaAttribute() ||
		Attribute == UPlayerAttributeSet::GetCooldownAttribute() ||
		Attribute == UPlayerAttributeSet::GetLuckAttribute() ||
		Attribute == UPlayerAttributeSet::GetGrowthAttribute() ||
		Attribute == UPlayerAttributeSet::GetGreedAttribute() ||
		Attribute == UPlayerAttributeSet::GetCurseAttribute())
	{
		ValueStr = TEXT("-");
		float Result = (ValueFloat-1.0f)*100.0f;
		ValueInt = static_cast<int>(Result);
		
		if (ValueInt > 0)
		{
			ValueStr = FString::Printf(TEXT("+%d%%"), ValueInt);
		}
		else
		if (ValueInt < 0)
		{
			ValueStr = FString::Printf(TEXT("%d%%"), ValueInt);
		}
		
	}
	else
	if (Attribute == UPlayerAttributeSet::GetRecoveryAttribute())
	{
		ValueStr = FString::SanitizeFloat(ValueFloat, 2);
	}
	else
	if (Attribute != UPlayerAttributeSet::GetMaxHealthAttribute() && Attribute != UPlayerAttributeSet::GetMagnetAttribute())
	{
		if (ValueInt > 0)
		{
			ValueStr.InsertAt(0, TEXT("+"));
		}
		else
		if (ValueInt < 0)
		{
			ValueStr.InsertAt(0, TEXT("-"));
		}
	}
}

void UPauseOverlayWidgetController::AttributeChanged(const FOnAttributeChangeData& Data)
{
	FString Name;
	FString ValueStr;
	GetAttributeNameAndValue(Data.Attribute, Data.NewValue, Name, ValueStr);

	FGameplayTag Tag;
	for (TTuple<FGameplayTag, FGameplayAttribute(*)()>& Elem : GetPlayerAttributeSet()->AllAttributes)
	{
		FGameplayAttribute Attribute = Elem.Value();
		if (Data.Attribute == Attribute)
		{
			Tag = Elem.Key;
			break;
		}
	}

	OnPlayerAttributeValueChanged.Broadcast(Name, ValueStr, Tag);
}
