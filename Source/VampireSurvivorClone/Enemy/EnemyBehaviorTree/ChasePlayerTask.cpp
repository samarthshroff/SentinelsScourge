// Fill out your copyright notice in the Description page of Project Settings.


#include "ChasePlayerTask.h"

#include "EnemyAIController.h"
#include "VampireSurvivorClone/Enemy/EnemyCharacterBase.h"
#include "VampireSurvivorClone/Enemy/EnemyStates.h"

UChasePlayerTask::UChasePlayerTask()
{
	ChaseSpeed = 500.0f;
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
	ControlledCharacter->UpdateWalkSpeed(ChaseSpeed);
	ControlledCharacter->UpdateCurrentState(UEnemyStates::Chasing);	

	return EBTNodeResult::Succeeded;
}
