	// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "Enemy/EnemyBehaviorTree/EnemyBehaviorTree.h"

#include "Enemy/EnemyBehaviorTree/ChasePlayerTask.h"
#include "Enemy/EnemyBehaviorTree/EnemyBlackboard.h"
#include "BehaviorTree/Composites/BTComposite_Selector.h"
#include "BehaviorTree/Composites/BTComposite_Sequence.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BehaviorTree/Tasks/BTTask_RotateToFaceBBEntry.h"

UEnemyBehaviorTree::UEnemyBehaviorTree()
{
		
}

void UEnemyBehaviorTree::Initialize()
{
	BlackboardAsset = NewObject<UEnemyBlackboard>(this, TEXT("BlackBoardData"));
	EnemyBlackboard = Cast<UEnemyBlackboard>(BlackboardAsset);
	EnemyBlackboard->Initialize();
	
	RootNode = NewObject<UBTComposite_Selector>(this, TEXT("AI Root"));
	
	ChaseNode = NewObject<UBTComposite_Sequence>(RootNode, TEXT("ChasePlayer"));
	
	RotateToFacePlayer = NewObject<UBTTask_RotateToFaceBBEntry>(ChaseNode, TEXT("RotateToFacePlayer"));
	if (!EnemyBlackboard->SetTargetActorAsBlackboardKey(RotateToFacePlayer))
	{
		UE_LOG(LogTemp, Log, TEXT("Could not set the blackboard key for RotateToFacePlayer"));
	}

	ChasePlayer = NewObject<UChasePlayerTask>(ChaseNode, TEXT("ChasePlayer"));
	MoveToPlayer = NewObject<UBTTask_MoveTo>(ChaseNode, TEXT("MoveToPlayer"));
	if (!EnemyBlackboard->SetTargetActorAsBlackboardKey(MoveToPlayer))
	{
		UE_LOG(LogTemp, Log, TEXT("Could not set the blackboard key for MoveToPlayer"));
	}
	
	ChaseNode->Children.Add({ .ChildTask = RotateToFacePlayer});
	ChaseNode->Children.Add({ .ChildTask = ChasePlayer});
	ChaseNode->Children.Add({ .ChildTask = MoveToPlayer});
	
	RootNode->Children.Add(FBTCompositeChild(ChaseNode));
}
