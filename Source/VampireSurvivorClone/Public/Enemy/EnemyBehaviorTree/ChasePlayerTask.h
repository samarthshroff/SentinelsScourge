// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChasePlayerTask.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORCLONE_API UChasePlayerTask : public UBTTaskNode
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly)
	float ChaseSpeed;

	UChasePlayerTask();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
