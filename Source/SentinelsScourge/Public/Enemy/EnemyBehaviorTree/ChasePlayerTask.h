// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

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
