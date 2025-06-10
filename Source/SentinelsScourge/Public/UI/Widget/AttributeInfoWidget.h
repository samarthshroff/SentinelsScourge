// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UI/Widget/SSWidget.h"
#include "AttributeInfoWidget.generated.h"

/**
 *
 */
UCLASS()
class SENTINELSSCOURGE_API UAttributeInfoWidget : public USSWidget
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
