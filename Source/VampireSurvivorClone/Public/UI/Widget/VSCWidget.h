// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VSCWidget.generated.h"

class UVSCWidgetController;
/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UVSCWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UVSCWidgetController* Controller);
	
protected:	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UVSCWidgetController> WidgetController;

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();	
};
