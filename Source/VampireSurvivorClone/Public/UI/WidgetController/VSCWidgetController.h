// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VSCWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(Blueprintable)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY()
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;

	FWidgetControllerParams() {}
	
	FWidgetControllerParams(TObjectPtr<APlayerController> InPlayerController,
		TObjectPtr<APlayerState> InPlayerState, TObjectPtr<UAbilitySystemComponent> InAbilitySystemComponent, TObjectPtr<UAttributeSet> InAttributeSet) :
		PlayerController(InPlayerController), PlayerState(InPlayerState), AbilitySystemComponent
		(InAbilitySystemComponent), AttributeSet(InAttributeSet)
	{
		
	}
	
};

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UVSCWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& InWidgetControllerParams);

	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependencies();
	
protected:
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
