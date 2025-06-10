// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

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
