// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SSGameplayAbilityInterface.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
// This class does not need to be modified.
UINTERFACE()
class USSGameplayAbilityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Contract for all abilities from this project.
 */
class SENTINELSSCOURGE_API ISSGameplayAbilityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Initialize(float InCooldown);
};
