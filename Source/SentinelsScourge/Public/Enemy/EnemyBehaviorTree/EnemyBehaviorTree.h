// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyBehaviorTree.generated.h"

class UBTTask_MoveTo;
class UChasePlayerTask;
class UBTTask_RotateToFaceBBEntry;
class UEnemyBlackboard;
class UBTComposite_Sequence;
/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class SENTINELSSCOURGE_API UEnemyBehaviorTree : public UBehaviorTree
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnemyBlackboard> EnemyBlackboard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBTComposite_Sequence> ChaseNode;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBTTask_RotateToFaceBBEntry> RotateToFacePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UChasePlayerTask> ChasePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBTTask_MoveTo> MoveToPlayer;

	UEnemyBehaviorTree();
	void Initialize();
};
