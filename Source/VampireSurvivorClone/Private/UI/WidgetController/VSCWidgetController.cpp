// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/VSCWidgetController.h"

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
