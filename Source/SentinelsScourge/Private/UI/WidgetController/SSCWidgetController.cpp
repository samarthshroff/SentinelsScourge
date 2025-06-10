// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "UI/WidgetController/SSCWidgetController.h"

#include "AbilitySystem/PlayerAttributeSet.h"

void USSCWidgetController::SetWidgetControllerParams(const FWidgetControllerParams &InWidgetControllerParams)
{
	PlayerController = InWidgetControllerParams.PlayerController;
	PlayerState = InWidgetControllerParams.PlayerState;
	AbilitySystemComponent = InWidgetControllerParams.AbilitySystemComponent;
	AttributeSet = InWidgetControllerParams.AttributeSet;
}

void USSCWidgetController::BroadcastInitialValues()
{
}

void USSCWidgetController::BindCallbacksToDependencies()
{
}

void USSCWidgetController::Initialize()
{
}

// void USSCWidgetController::Initialize()
// {
// }
TObjectPtr<UPlayerAttributeSet> USSCWidgetController::GetPlayerAttributeSet()
{
	if (PlayerAttributeSet == nullptr)
	{
		PlayerAttributeSet = Cast<UPlayerAttributeSet>(AttributeSet);
	}
	return PlayerAttributeSet;
}
