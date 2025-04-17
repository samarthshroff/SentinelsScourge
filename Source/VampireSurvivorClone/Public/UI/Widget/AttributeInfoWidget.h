// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UI/Widget/VSWidget.h"
#include "AttributeInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UAttributeInfoWidget : public UVSWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	FText AttributeName;

	UPROPERTY(BlueprintReadOnly)
	FText AttributeValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttribute Attribute;
};
