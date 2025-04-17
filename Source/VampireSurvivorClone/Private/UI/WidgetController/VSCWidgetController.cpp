// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/VSCWidgetController.h"

#include "AbilitySystem/PlayerAttributeSet.h"

void UVSCWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams)
{
	PlayerController = InWidgetControllerParams.PlayerController;
	PlayerState = InWidgetControllerParams.PlayerState;
	AbilitySystemComponent = InWidgetControllerParams.AbilitySystemComponent;
	AttributeSet = InWidgetControllerParams.AttributeSet;
}

void UVSCWidgetController::BroadcastInitialValues()
{
}

void UVSCWidgetController::BindCallbacksToDependencies()
{
}

// void UVSCWidgetController::Initialize()
// {
// }
TObjectPtr<UPlayerAttributeSet> UVSCWidgetController::GetPlayerAttributeSet()
{
	if (PlayerAttributeSet == nullptr)
	{
		PlayerAttributeSet = Cast<UPlayerAttributeSet>(AttributeSet);
	}
	return PlayerAttributeSet;
}
