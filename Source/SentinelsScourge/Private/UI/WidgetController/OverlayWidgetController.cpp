// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/PlayerAttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widget/SSWidget.h"
#include "UI/WidgetController/LevelUpOverlayWidgetController.h"
#include "UI/WidgetController/PauseOverlayWidgetController.h"

TObjectPtr<UPauseOverlayWidgetController> UOverlayWidgetController::GetPauseWidgetController(const FWidgetControllerParams &WidgetControllerParams)
{
	if (PauseOverlayWidgetController == nullptr)
	{
		PauseOverlayWidgetController = NewObject<UPauseOverlayWidgetController>(this, UPauseOverlayWidgetController::StaticClass());
		PauseOverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		PauseOverlayWidgetController->BindCallbacksToDependencies();
		PauseOverlayWidgetController->Initialize();
	}

	return PauseOverlayWidgetController;
}

TObjectPtr<ULevelUpOverlayWidgetController> UOverlayWidgetController::GetLevelUpOverlayWidgetController(const FWidgetControllerParams &WidgetControllerParams)
{
	if (LevelUpOverlayWidgetController == nullptr)
	{
		LevelUpOverlayWidgetController = NewObject<ULevelUpOverlayWidgetController>(this, ULevelUpOverlayWidgetController::StaticClass());
		LevelUpOverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		LevelUpOverlayWidgetController->BindCallbacksToDependencies();
		LevelUpOverlayWidgetController->Initialize();
	}

	return LevelUpOverlayWidgetController;
}

void UOverlayWidgetController::HeroXPChanged(const FOnAttributeChangeData &Data)
{
	OnHeroXPChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HeroMaxXPChanged(const FOnAttributeChangeData &Data)
{
	OnHeroMaxXPChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::HeroLevelChanged(const FOnAttributeChangeData &Data)
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	CurrentlyShowing = ECurrentlyShowingMenu::LevelUpMenu;

	UUserWidget *UserWidget = CreateWidget<UUserWidget>(GetWorld(), LevelUpOverlayWidgetClass);
	LevelUpOverlayWidget = Cast<USSWidget>(UserWidget);

	const FWidgetControllerParams WidgetControllerParams(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
	ULevelUpOverlayWidgetController *LevelUpController = GetLevelUpOverlayWidgetController(WidgetControllerParams);

	UE_LOG(LogTemp, Log, TEXT("Before Adding Dynamic function for levelup overlay resume button"));
	LevelUpOverlayWidgetController->OnResumeButtonClickedDelegate.AddDynamic(this, &UOverlayWidgetController::OnLevelUpResumeButtonClicked);
	UE_LOG(LogTemp, Log, TEXT("After Adding Dynamic function for levelup overlay resume button"));
	LevelUpOverlayWidget->SetWidgetController(LevelUpOverlayWidgetController);
	UE_LOG(LogTemp, Log, TEXT("After setting the level up widget controller for the level up overlay widget"));
	UserWidget->AddToViewport();
	UserWidget->SetVisibility(ESlateVisibility::Hidden);
	LevelUpOverlayWidgetController->BroadcastInitialValues();
	UserWidget->SetVisibility(ESlateVisibility::Visible);

	LevelUpOverlayFocusChanged.Broadcast(true);
}

void UOverlayWidgetController::OnLevelUpResumeButtonClicked()
{
	LevelUpOverlayWidgetController->OnResumeButtonClickedDelegate.RemoveDynamic(this, &UOverlayWidgetController::OnLevelUpResumeButtonClicked);
	LevelUpOverlayWidget->RemoveFromParent();
	CurrentlyShowing = ECurrentlyShowingMenu::None;
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	LevelUpOverlayFocusChanged.Broadcast(false);
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetPlayerAttributeSet()->GetXPAttribute()).AddUObject(this, &UOverlayWidgetController::HeroXPChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetPlayerAttributeSet()->GetMaxXPAttribute()).AddUObject(this, &UOverlayWidgetController::HeroMaxXPChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetPlayerAttributeSet()->GetLevelAttribute()).AddUObject(this, &UOverlayWidgetController::HeroLevelChanged);
}

void UOverlayWidgetController::Initialize()
{
	Super::Initialize();
	CurrentlyShowing = ECurrentlyShowingMenu::None;
}

ECurrentlyShowingMenu UOverlayWidgetController::GetCurrentlyShowingMenu()
{
	return CurrentlyShowing;
}

void UOverlayWidgetController::BroadcastInitialValues()
{
	Super::BroadcastInitialValues();
	OnHeroXPChanged.Broadcast(GetPlayerAttributeSet()->GetXP());
	OnHeroMaxXPChanged.Broadcast(GetPlayerAttributeSet()->GetMaxXP());
}

void UOverlayWidgetController::OnPauseMenuResumeButtonClicked()
{
	PauseOverlayWidgetController->OnResumeButtonClickedDelegate.RemoveDynamic(this, &UOverlayWidgetController::OnPauseMenuResumeButtonClicked);
	CurrentlyShowing = ECurrentlyShowingMenu::None;
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UOverlayWidgetController::SetOtherOverlayWidgets(TSubclassOf<USSWidget> InPauseOverlayWidgetClass, TSubclassOf<USSWidget> InLevelUpOverlayWidgetClass)
{
	PauseOverlayWidgetClass = InPauseOverlayWidgetClass;
	LevelUpOverlayWidgetClass = InLevelUpOverlayWidgetClass;
}

void UOverlayWidgetController::OnPauseButtonClicked()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	CurrentlyShowing = ECurrentlyShowingMenu::PauseMenu;

	UUserWidget *UserWidget = CreateWidget<UUserWidget>(GetWorld(), PauseOverlayWidgetClass);
	PauseOverlayWidget = Cast<USSWidget>(UserWidget);

	const FWidgetControllerParams WidgetControllerParams(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
	UPauseOverlayWidgetController *PauseController = GetPauseWidgetController(WidgetControllerParams);

	PauseOverlayWidgetController->OnResumeButtonClickedDelegate.AddDynamic(this, &UOverlayWidgetController::OnPauseMenuResumeButtonClicked);
	PauseOverlayWidget->SetWidgetController(PauseOverlayWidgetController);
	UserWidget->AddToViewport();
	UserWidget->SetVisibility(ESlateVisibility::Hidden);
	PauseOverlayWidgetController->BroadcastInitialValues();
	UserWidget->SetVisibility(ESlateVisibility::Visible);
}
