// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/LevelUpOverlayWidgetController.h"

#include "AbilitySystem/PlayerAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widget/VSWidget.h"
#include "UI/WidgetController/AttributesMenuWidgetController.h"

void ULevelUpOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
}

void ULevelUpOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
}

void ULevelUpOverlayWidgetController::Initialize()
{	
	const FWidgetControllerParams WidgetControllerParams(PlayerController, PlayerState,AbilitySystemComponent, AttributeSet);
	UAttributesMenuWidgetController* AttributesMenuController = GetAttributesMenuWidgetController(WidgetControllerParams);
}

void ULevelUpOverlayWidgetController::UpdateAttributesMenu(UVSWidget* InAttributesMenuWidget)
{
	AttributesMenuWidget = InAttributesMenuWidget;
	const FWidgetControllerParams WidgetControllerParams(PlayerController, PlayerState,AbilitySystemComponent, AttributeSet);
	UAttributesMenuWidgetController* AttributesMenuController = GetAttributesMenuWidgetController(WidgetControllerParams);
	AttributesMenuWidget->SetWidgetController(AttributesMenuController);		
	//AttributesMenuWidget->SetVisibility(ESlateVisibility::Hidden);
	AttributesMenuController->BroadcastInitialValues();
	//AttributesMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

TObjectPtr<UAttributesMenuWidgetController> ULevelUpOverlayWidgetController::GetAttributesMenuWidgetController(
	const FWidgetControllerParams& WidgetControllerParams)
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

void ULevelUpOverlayWidgetController::OnResumeButtonClicked()
{	
	OnResumeButtonClickedDelegate.Broadcast();
	Cast<UPlayerAttributeSet>(AttributeSet)->UpdateXPs();
}
