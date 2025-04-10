// Fill out your copyright notice in the Description page of Project Settings.


#include "GPAttributeBPFuncLib.h"

#include "AbilitySystem/PlayerAttributeSet.h"

FGameplayAttribute UGPAttributeBPFuncLib::GetPlayerAttribute(FName PropertyName)
{
	return FindFieldChecked<FProperty>(UPlayerAttributeSet::StaticClass(), PropertyName);
}
