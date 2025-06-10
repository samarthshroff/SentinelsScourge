// Fill out your copyright notice in the Description page of Project Settings.

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
