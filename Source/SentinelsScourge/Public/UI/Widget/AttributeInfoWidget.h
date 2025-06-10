// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

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
