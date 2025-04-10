// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GPAttributeBPFuncLib.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UGPAttributeBPFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Python")
	static FGameplayAttribute GetPlayerAttribute(FName PropertyName);
	
};
