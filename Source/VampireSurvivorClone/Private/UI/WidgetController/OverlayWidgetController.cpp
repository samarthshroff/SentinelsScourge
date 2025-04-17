// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widget/VSWidget.h"
#include "UI/WidgetController/PauseOverlayWidgetController.h"

TObjectPtr<UPauseOverlayWidgetController> UOverlayWidgetController::GetPauseWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (PauseOverlayWidgetController == nullptr)
	{
		PauseOverlayWidgetController = NewObject<UPauseOverlayWidgetController>(this, UPauseOverlayWidgetController::StaticClass());
		PauseOverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		PauseOverlayWidgetController->BindCallbacksToDependencies();
	}
	
	return PauseOverlayWidgetController;
}

void UOverlayWidgetController::SetPauseOverlayWidget(TSubclassOf<UVSWidget> InPauseOverlayWidgetClass)
{
	PauseOverlayWidgetClass = InPauseOverlayWidgetClass; 
}

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
}

void UOverlayWidgetController::OnPauseButtonClicked()
{
	UGameplayStatics::SetGamePaused(GetWorld(),true);

	UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetWorld(), PauseOverlayWidgetClass);	
	PauseOverlayWidget = Cast<UVSWidget>(UserWidget);
	
	const FWidgetControllerParams WidgetControllerParams(PlayerController, PlayerState,AbilitySystemComponent, AttributeSet);
	UPauseOverlayWidgetController* PauseController = GetPauseWidgetController(WidgetControllerParams);

	PauseOverlayWidget->SetWidgetController(PauseOverlayWidgetController);		
	UserWidget->AddToViewport();
	UserWidget->SetVisibility(ESlateVisibility::Hidden);
	PauseOverlayWidgetController->BroadcastInitialValues();
	UserWidget->SetVisibility(ESlateVisibility::Visible);
}
