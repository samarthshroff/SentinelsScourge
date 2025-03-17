// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"

#include "EnemyAIConsts.h"
#include "EnemyBehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "VampireSurvivorClone/Enemy/EnemyStates.h"
#include "VampireSurvivorClone/PlayerCharacter/PlayerCharacter.h"


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
	// AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	// AIPerceptionComponent->SenseConfig
}

// Called when the game starts or when spawned
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("In BeginPlay"));
	if (BehaviorTree)
	{
		UE_LOG(LogTemp, Log, TEXT("Begin Play inside BehaviorTree if condition"));
		BehaviorTree->Initialize();
		if (BehaviorTree->BlackboardAsset)
		{
			BlackboardComponent->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
			BlackboardComponent->SetValueAsObject(TargetActorName, UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			BlackboardComponent->SetValueAsEnum(CurrentStateName, static_cast<uint8>(UEnemyStates::Idle));	
		}
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	//UE_LOG(LogTemp, Log, TEXT("In OnPossess"));	
	
	//UE_LOG(LogTemp, Log, TEXT("BehaviorTree %s"), *BehaviorTree->GetClass()->GetName() );
	if(BehaviorTree)
	{
		//UE_LOG(LogTemp, Log, TEXT("inside BehaviorTree if condition"));
		// BehaviorTree->Initialize();
		// if (BehaviorTree->BlackboardAsset)
		// {
		// 	BlackboardComponent->InitializeBlackboard(*(BehaviorTree->BlackboardAsset));
		// 	BlackboardComponent->SetValueAsObject(TargetActorName, UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		// 	BlackboardComponent->SetValueAsEnum(CurrentStateName, static_cast<uint8>(UEnemyStates::Idle));	
		// }

		//UE_LOG(LogTemp, Log, TEXT("before run BehaviorTree "));
		RunBehaviorTree( BehaviorTree );
	}
}

// Called every frame
void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

