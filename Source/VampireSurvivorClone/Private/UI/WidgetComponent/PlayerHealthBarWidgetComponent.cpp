// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetComponent/PlayerHealthBarWidgetComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/Widget/VSCWidget.h"
#include "UI/WidgetController/VSCWidgetController.h"

UPlayerHealthBarWidgetComponent::UPlayerHealthBarWidgetComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerHealthBarWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(),0);	
}

TObjectPtr<UVSCWidgetController> UPlayerHealthBarWidgetComponent::GetWidgetController(
	const FWidgetControllerParams& WidgetControllerParams)
{
	if (WidgetController == nullptr)
	{
		WidgetController = NewObject<UVSCWidgetController>(this, UVSCWidgetController::StaticClass());
		WidgetController->SetWidgetControllerParams(WidgetControllerParams);
	}
	
	return WidgetController;
}

void UPlayerHealthBarWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerCameraManager)
	{
		const FRotator Angle = UKismetMathLibrary::FindLookAtRotation(this->GetComponentLocation(),
										PlayerCameraManager->GetCameraLocation());
		this->SetWorldRotation(Angle);
	}
}

void UPlayerHealthBarWidgetComponent::Initialize(TObjectPtr<APlayerController> InPlayerController,
	TObjectPtr<APlayerState> InPlayerState, TObjectPtr<UAbilitySystemComponent> InAbilitySystemComponent,
	TObjectPtr<UAttributeSet> InAttributeSet,
		TSubclassOf<UVSCWidget> HealthBarWidgetClass)
{
	if (GetWidget() == nullptr)
	{
		SetWidgetClass( GetWidgetClass() != nullptr?GetWidgetClass(): HealthBarWidgetClass);
		UUserWidget* UserWidget = CreateWidget(GetWorld(), HealthBarWidgetClass);
		SetWidget(UserWidget);
		//UpdateWidget();
	}
	//checkf(WidgetClass, TEXT("UPlayerHealthBarWidgetComponent::Initialize: Widget class is null. Please fill it in Associate Blueprint."));
	UVSCWidget* VSCWidget = Cast<UVSCWidget>(GetWidget());

	FWidgetControllerParams WidgetControllerParams(InPlayerController, InPlayerState, InAbilitySystemComponent, InAttributeSet);
	VSCWidget->SetWidgetController(GetWidgetController(WidgetControllerParams));	
}
