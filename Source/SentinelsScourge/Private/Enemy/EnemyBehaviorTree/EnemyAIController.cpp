// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/EnemyBehaviorTree/EnemyAIController.h"

#include "Enemy/EnemyBehaviorTree/EnemyAIConsts.h"
#include "Enemy/EnemyBehaviorTree/EnemyBehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Enemy/EnemyStates.h"
#include "SentinelsScourge/Public/Player/PlayerCharacter.h"

// Sets default values
AEnemyAIController::AEnemyAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bStartAILogicOnPossess = true;
	// Initialize Blackboard and Behavior Tree Components
	BehaviorTree = NewObject<UEnemyBehaviorTree>(this, TEXT("BehaviorTree"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

// Called when the game starts or when spawned
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (BehaviorTree)
	{
		BehaviorTree->Initialize();
		if (BehaviorTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
			const APlayerController *LocalPlayerController = GetWorld()->GetFirstPlayerController();
			BlackboardComponent->SetValueAsObject(TargetActorName, Cast<APlayerCharacter>(LocalPlayerController->GetPawn()));
			BlackboardComponent->SetValueAsEnum(CurrentStateName, static_cast<uint8>(UEnemyStates::Idle));
		}
	}
}

void AEnemyAIController::OnPossess(APawn *InPawn)
{
	Super::OnPossess(InPawn);
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}

// Called every frame
void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
