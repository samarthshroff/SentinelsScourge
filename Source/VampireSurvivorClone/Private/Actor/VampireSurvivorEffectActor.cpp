// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/VampireSurvivorEffectActor.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "AbilitySystemGlobals.h"

// Sets default values
AVampireSurvivorEffectActor::AVampireSurvivorEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetByCallerValues.Reset();
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = SceneRoot;
}

// Called when the game starts or when spawned
void AVampireSurvivorEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AVampireSurvivorEffectActor::OnBeginOverlap(AActor* TargetActor, const float Level)
{
	if (InstantGameplayEffectClass != nullptr && InstantGEApplicationPolicy == EGameplayEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyGamePlayEffectToTarget(TargetActor, InstantGameplayEffectClass, Level);
	}
	if (HasDurationGameplayEffectClass != nullptr && HasDurationGEApplicationPolicy == EGameplayEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyGamePlayEffectToTarget(TargetActor, HasDurationGameplayEffectClass, Level);
	}
	if (InfiniteGameplayEffectClass != nullptr && InfiniteGEApplicationPolicy == EGameplayEffectApplicationPolicy::ApplyOnBeginOverlap)
	{
		ApplyGamePlayEffectToTarget(TargetActor, InfiniteGameplayEffectClass, Level);
	}
}

void AVampireSurvivorEffectActor::OnEndOverlap(AActor* TargetActor, const float Level)
{
	if (InstantGameplayEffectClass != nullptr && InstantGEApplicationPolicy == EGameplayEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyGamePlayEffectToTarget(TargetActor, InstantGameplayEffectClass, Level);
	}
	if (HasDurationGameplayEffectClass != nullptr && HasDurationGEApplicationPolicy == EGameplayEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyGamePlayEffectToTarget(TargetActor, HasDurationGameplayEffectClass, Level);
	}
	if (InfiniteGameplayEffectClass != nullptr && InfiniteGEApplicationPolicy == EGameplayEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyGamePlayEffectToTarget(TargetActor, InfiniteGameplayEffectClass, Level);
	}
	if (InfiniteGameplayEffectClass != nullptr && InfiniteGERemovalPolicy == EGameplayEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor, true);
		if (AbilitySystemComponent == nullptr)
		{
			return;
		}

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (const TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> Elem : InfiniteActiveGEHandles)
		{
			if (Elem.Value == AbilitySystemComponent)
			{
				AbilitySystemComponent->RemoveActiveGameplayEffect(Elem.Key, 1);
				HandlesToRemove.Add(Elem.Key);
			}
		}
		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			InfiniteActiveGEHandles.Remove(Handle);
		}
		if (bShouldDestroyOnRemoval)
			Destroy();
	}
}

void AVampireSurvivorEffectActor::ApplyGamePlayEffectToTarget(const AActor* TargetActor, const TSubclassOf<UGameplayEffect>& InGameplayEffectClass, const float Level)
{
	UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor, true);
	if (AbilitySystemComponent == nullptr) return;
	
	check(InGameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(InGameplayEffectClass, Level, ContextHandle);

	if (SetByCallerValues.Num() > 0)
	{
		for (TTuple<FGameplayTag, float> TagValuePair : SetByCallerValues)
		{			
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(TagValuePair.Key, TagValuePair.Value);			
		}
	}	
	
	const FActiveGameplayEffectHandle ActiveHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

	if (SpecHandle.Data.Get()->Def->DurationPolicy == EGameplayEffectDurationType::Infinite &&
		InfiniteGERemovalPolicy == EGameplayEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		InfiniteActiveGEHandles.Add(ActiveHandle, AbilitySystemComponent);	
	}
}

