// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "PlayerHealthBarWidgetComponent.generated.h"

class UPlayerHealthWidgetController;
class UVSCWidget;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UVSCWidgetController;
/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UPlayerHealthBarWidgetComponent : public UWidgetComponent
{
	GENERATED_UCLASS_BODY()

private:
	UPROPERTY()
	TObjectPtr<APlayerCameraManager> PlayerCameraManager;

	UPROPERTY()
	TObjectPtr<UPlayerHealthWidgetController> PlayerHealthWidgetController;

protected:
	virtual void BeginPlay() override;
	virtual void OnRegister() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) override;
	
public:
	TObjectPtr<UPlayerHealthWidgetController> GetWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	void Initialize(TObjectPtr<APlayerController> InPlayerController,
		TObjectPtr<APlayerState> InPlayerState, TObjectPtr<UAbilitySystemComponent> InAbilitySystemComponent, TObjectPtr<UAttributeSet> InAttributeSet);
};
