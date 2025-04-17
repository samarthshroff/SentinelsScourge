// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/VSCWidgetController.h"
#include "OverlayWidgetController.generated.h"

class UPauseOverlayWidgetController;
class UVSWidget;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class VAMPIRESURVIVORCLONE_API UOverlayWidgetController : public UVSCWidgetController
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TObjectPtr<UVSWidget> PauseOverlayWidget;

	UPROPERTY()
	TSubclassOf<UVSWidget> PauseOverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UPauseOverlayWidgetController> PauseOverlayWidgetController;	
	
public:
	void SetPauseOverlayWidget(TSubclassOf<UVSWidget> InPauseOverlayWidgetClass);
	virtual void BroadcastInitialValues() override;

	UFUNCTION(BlueprintCallable)
	void OnPauseButtonClicked();

	TObjectPtr<UPauseOverlayWidgetController> GetPauseWidgetController(const FWidgetControllerParams& WidgetControllerParams);
	
};
