// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "UI/HUD/SSHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/SSWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

TObjectPtr<UOverlayWidgetController> ASSHUD::GetOverlayWidgetController(const FWidgetControllerParams &WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, UOverlayWidgetController::StaticClass());
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}

	return OverlayWidgetController;
}

void ASSHUD::Initialize(const FWidgetControllerParams &WidgetControllerParams)
{
	UUserWidget *Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<USSWidget>(Widget);
	UOverlayWidgetController *WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidgetController->SetOtherOverlayWidgets(PauseOverlayWidgetClass, LevelUpOverlayWidgetClass);
	OverlayWidgetController->BroadcastInitialValues();
	OverlayWidgetController->Initialize();

	Widget->AddToViewport();
}
