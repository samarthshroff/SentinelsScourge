// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VSHUD.generated.h"

struct FWidgetControllerParams;
class UOverlayWidgetController;
class UVSWidget;
/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API AVSHUD : public AHUD
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TObjectPtr<UVSWidget> OverlayWidget;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;	
	
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UVSWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UVSWidget> PauseOverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UVSWidget> LevelUpOverlayWidgetClass;
	
public:
	void Initialize(const FWidgetControllerParams& WidgetControllerParams);
	TObjectPtr<UOverlayWidgetController> GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);
};
