// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"

#include "AbilitySystemComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ACharacterBase::GetAttributeSetComponent() const
{
	return AttributeSet;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
// void ACharacterBase::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// }

FActiveGameplayEffectHandle ACharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> AttributesGameplayEffect, float Level)
{
	check(AbilitySystemComponent);
	check(AttributesGameplayEffect);

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(AttributesGameplayEffect, Level,ContextHandle);
	return AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);	
}

void ACharacterBase::InitializeAttributes()
{
	/*I may not have to remove any of these as the default attribute Gameplay effect is instant and the modifiers override.
	 *May remove this after wards if deemed unnecessary*/
	// Either just remove the bonus on start of every run OR remove only when character is changed.
	if (BonusAttributesEffectHandle.IsValid())
		AbilitySystemComponent->RemoveActiveGameplayEffect(BonusAttributesEffectHandle);
	if (PowerUpsAttributesEffectHandle.IsValid())
		AbilitySystemComponent->RemoveActiveGameplayEffect(PowerUpsAttributesEffectHandle);
	if (PassiveItemsAttributesEffectHandle.IsValid())
		AbilitySystemComponent->RemoveActiveGameplayEffect(PassiveItemsAttributesEffectHandle);
	if (ArcanasAttributesEffectHandle.IsValid())
		AbilitySystemComponent->RemoveActiveGameplayEffect(ArcanasAttributesEffectHandle);

	
	
	ApplyEffectToSelf(DefaultAttributes, 1.0f);
	
	if (BonusAttributes != nullptr)
		BonusAttributesEffectHandle = ApplyEffectToSelf(BonusAttributes,1.0f);
	
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

