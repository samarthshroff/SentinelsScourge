// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/VSHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/VSWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

TObjectPtr<UOverlayWidgetController> AVSHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, UOverlayWidgetController::StaticClass());
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	
	return OverlayWidgetController;
}

void AVSHUD::Initialize(const FWidgetControllerParams& WidgetControllerParams)
{
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(),OverlayWidgetClass);
	OverlayWidget = Cast<UVSWidget>(Widget);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(OverlayWidgetController);
	OverlayWidgetController->SetPauseOverlayWidget(PauseOverlayWidgetClass);
	OverlayWidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}
