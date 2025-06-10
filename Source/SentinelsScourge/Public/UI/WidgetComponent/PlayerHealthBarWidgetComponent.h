// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "PlayerHealthBarWidgetComponent.generated.h"

class UPlayerHealthWidgetController;
class USSWidget;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class USSCWidgetController;
/**
 *
 */
UCLASS()
class SENTINELSSCOURGE_API UPlayerHealthBarWidgetComponent : public UWidgetComponent
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
							   FActorComponentTickFunction *ThisTickFunction) override;

public:
	TObjectPtr<UPlayerHealthWidgetController> GetWidgetController(const FWidgetControllerParams &WidgetControllerParams);

	void Initialize(const FWidgetControllerParams &WidgetControllerParams);
};
