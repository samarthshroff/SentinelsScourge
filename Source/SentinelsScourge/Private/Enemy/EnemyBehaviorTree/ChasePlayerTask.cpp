// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "Enemy/EnemyBehaviorTree/ChasePlayerTask.h"

#include "Enemy/EnemyBehaviorTree/EnemyAIController.h"
#include "Enemy/EnemyCharacterBase.h"
#include "Enemy/EnemyStates.h"

UChasePlayerTask::UChasePlayerTask()
{
}

EBTNodeResult::Type UChasePlayerTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	// Get the AI Controller
	const TObjectPtr<AEnemyAIController> AIController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	// Get the Pawn controlled by the AI
	TObjectPtr<AEnemyCharacterBase> ControlledCharacter = Cast<AEnemyCharacterBase>(AIController->GetCharacter());
	if (!ControlledCharacter)
	{		
		return EBTNodeResult::Failed;
	}
	
	ControlledCharacter->UpdateCurrentState(UEnemyStates::Chasing);
	return EBTNodeResult::Succeeded;
}
