// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "UI/WidgetController/PauseOverlayWidgetController.h"

#include "Kismet/GameplayStatics.h"
#include "UI/Widget/SSWidget.h"
#include "UI/WidgetController/AttributesMenuWidgetController.h"

void UPauseOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
}

void UPauseOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
}

void UPauseOverlayWidgetController::OnResumeButtonClicked()
{
	OnResumeButtonClickedDelegate.Broadcast();
}

void UPauseOverlayWidgetController::Initialize()
{
	const FWidgetControllerParams WidgetControllerParams(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
	UAttributesMenuWidgetController *AttributesMenuController = GetAttributesMenuWidgetController(WidgetControllerParams);
}

void UPauseOverlayWidgetController::UpdateAttributesMenu(USSWidget *InAttributesMenuWidget)
{
	AttributesMenuWidget = InAttributesMenuWidget;
	const FWidgetControllerParams WidgetControllerParams(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
	UAttributesMenuWidgetController *AttributesMenuController = GetAttributesMenuWidgetController(WidgetControllerParams);
	AttributesMenuWidget->SetWidgetController(AttributesMenuController);
	// AttributesMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	AttributesMenuController->BroadcastInitialValues();
	// AttributesMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

TObjectPtr<UAttributesMenuWidgetController> UPauseOverlayWidgetController::GetAttributesMenuWidgetController(
	const FWidgetControllerParams &WidgetControllerParams)
{
	if (AttributesMenuWidgetController == nullptr)
	{
		AttributesMenuWidgetController = NewObject<UAttributesMenuWidgetController>(this, UAttributesMenuWidgetController::StaticClass());
		AttributesMenuWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		AttributesMenuWidgetController->BindCallbacksToDependencies();
		AttributesMenuWidgetController->Initialize();
	}

	return AttributesMenuWidgetController;
}
