// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyBehaviorTree/EnemyBlackboard.h"

#include "Enemy/EnemyBehaviorTree/EnemyAIConsts.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "Runtime/AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Enemy/EnemyStates.h"
#include "VampireSurvivorClone/Public/Player/PlayerCharacter.h"
// #include "VampireSurvivorClone/Enemy/EnemyStates.h"
// #include "VampireSurvivorClone/PlayerCharacter/PlayerCharacter.h"

UEnemyBlackboard::UEnemyBlackboard()
{
	
}

void UEnemyBlackboard::Initialize()
{
	TargetActor = NewObject<UBlackboardKeyType_Object>(this);	
	TargetActor->BaseClass = APlayerCharacter::StaticClass();	

	CurrentState = NewObject<UBlackboardKeyType_Enum>(this);
	CurrentState->EnumType = StaticEnum<UEnemyStates>();
	CurrentState->EnumName = FString("UEnemyStates");
	//CurrentState->DefaultValue = static_cast<uint8>(UEnemyStates::Idle);
	
	// Add the player character key entry to the black board.
	FBlackboardEntry Entry;
	Entry.EntryName = TargetActorName;
	Entry.KeyType = TargetActor;
	Keys.Add(Entry);

	Entry.EntryName = CurrentStateName;
	Entry.KeyType = CurrentState;
	Keys.Add(Entry);
	
	KeySelector = MakeShared<FBlackboardKeySelector>();
	KeySelector->SelectedKeyName = TargetActorName;
	KeySelector->SelectedKeyType = UBlackboardKeyType_Object::StaticClass();
	KeySelector->ResolveSelectedKey(*this);
	check( static_cast<int32>(KeySelector->GetSelectedKeyID() ) >= 0 );
	check(KeySelector->GetSelectedKeyID() != FBlackboard::InvalidKey );
}

bool UEnemyBlackboard::SetTargetActorAsBlackboardKey(const TObjectPtr<UObject>& Target) const
{
	if (Target != nullptr)
	{
		if (const FStructProperty* Prop = FindFieldChecked<FStructProperty>(Target->GetClass(), BlackboardKey))
		{
			Prop->SetValue_InContainer(Target, KeySelector.Get());
			return true;
		}
	}
	return false;
}
