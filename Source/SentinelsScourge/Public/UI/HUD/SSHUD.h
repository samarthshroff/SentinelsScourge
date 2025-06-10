// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SSHUD.generated.h"

struct FWidgetControllerParams;
class UOverlayWidgetController;
class USSWidget;
/**
 *
 */
UCLASS()
class SENTINELSSCOURGE_API ASSHUD : public AHUD
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TObjectPtr<USSWidget> OverlayWidget;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USSWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USSWidget> PauseOverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USSWidget> LevelUpOverlayWidgetClass;

public:
	void Initialize(const FWidgetControllerParams &WidgetControllerParams);
	TObjectPtr<UOverlayWidgetController> GetOverlayWidgetController(const FWidgetControllerParams &WidgetControllerParams);
};
