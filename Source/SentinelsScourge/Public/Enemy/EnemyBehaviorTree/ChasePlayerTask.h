// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChasePlayerTask.generated.h"

/**
 *
 */
UCLASS()
class SENTINELSSCOURGE_API UChasePlayerTask : public UBTTaskNode
{
	GENERATED_BODY()

	UChasePlayerTask();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
