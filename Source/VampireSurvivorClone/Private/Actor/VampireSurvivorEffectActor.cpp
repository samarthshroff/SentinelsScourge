// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/VampireSurvivorEffectActor.h"

#include "AbilitySystem/PlayerAttributeSet.h"
#include "Player/PlayerCharacter.h"
#include "AbilitySystemGlobals.h"

// Sets default values
AVampireSurvivorEffectActor::AVampireSurvivorEffectActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = SceneRoot;
}

// Called when the game starts or when spawned
void AVampireSurvivorEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AVampireSurvivorEffectActor::ApplyGamePlayEffectToTarget(const AActor* TargetActor, const TSubclassOf<UGameplayEffect>& InGameplayEffectClass, const bool ShouldDestroySelf)
{
	if(TargetActor && TargetActor->IsA(APlayerCharacter::StaticClass()))
	{
		check(InGameplayEffectClass);
		UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor, true);
		FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		ContextHandle.AddSourceObject(this);		
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(InGameplayEffectClass, 1.0f, ContextHandle);
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

		if (ShouldDestroySelf)
			Destroy();
	}
}

