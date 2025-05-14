// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/PlayerAttributeSet.h"
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

void UOverlayWidgetController::HeroXPChanged(const FOnAttributeChangeData& Data)
{
	OnHeroXPChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HeroMaxXPChanged(const FOnAttributeChangeData& Data)
{
	OnHeroMaxXPChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetPlayerAttributeSet()->GetXPAttribute()).AddUObject(this, &UOverlayWidgetController::HeroXPChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetPlayerAttributeSet()->GetMaxXPAttribute()).AddUObject(this, &UOverlayWidgetController::HeroMaxXPChanged);
}

void UOverlayWidgetController::SetPauseOverlayWidget(TSubclassOf<UVSWidget> InPauseOverlayWidgetClass)
{
	PauseOverlayWidgetClass = InPauseOverlayWidgetClass; 
}

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	OnHeroXPChanged.Broadcast(GetPlayerAttributeSet()->GetXP());
	OnHeroMaxXPChanged.Broadcast(GetPlayerAttributeSet()->GetMaxXP());
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
