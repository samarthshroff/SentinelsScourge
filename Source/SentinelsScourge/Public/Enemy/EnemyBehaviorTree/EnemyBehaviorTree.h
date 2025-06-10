// Fill out your copyright notice in the Description page of Project Settings.

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
