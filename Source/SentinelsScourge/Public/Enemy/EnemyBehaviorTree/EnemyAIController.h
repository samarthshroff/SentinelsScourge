// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "EnemyAIController.generated.h"

class UBehaviorTreeComponent;
class UEnemyBehaviorTree;

UCLASS()
class SENTINELSSCOURGE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

	// blackboard component, uses the blackboard owned by the behavior tree
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBlackboardComponent> BlackboardComponent;

	// private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UEnemyBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn *InPawn) override;

public:
	// Sets default values for this actor's properties
	AEnemyAIController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
