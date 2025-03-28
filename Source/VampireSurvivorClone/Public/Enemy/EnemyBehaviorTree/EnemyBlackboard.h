// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardData.h"
#include "EnemyBlackboard.generated.h"

class UBlackboardKeyType_Object;
class UBlackboardKeyType_Enum;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class VAMPIRESURVIVORCLONE_API UEnemyBlackboard : public UBlackboardData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlackboardKeyType_Object> TargetActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBlackboardKeyType_Enum> CurrentState;

	UEnemyBlackboard();
	void Initialize();
	bool SetTargetActorAsBlackboardKey(const TObjectPtr<UObject>& Target) const;

private:
	TSharedPtr<FBlackboardKeySelector> KeySelector;
};
