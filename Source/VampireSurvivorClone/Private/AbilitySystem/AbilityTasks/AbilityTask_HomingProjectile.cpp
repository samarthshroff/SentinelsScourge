// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AbilityTask_HomingProjectile.h"

#include "AbilitySystem/WeaponAttributeSet.h"
#include "Character/CharacterBaseInterface.h"
#include "Components/SphereComponent.h"
#include "Weapon/WeaponManager.h"
#include "Weapon/Homing/ProjectileHoming.h"

UAbilityTask_HomingProjectile::UAbilityTask_HomingProjectile(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	bTickingTask = true;
}

UAbilityTask_HomingProjectile* UAbilityTask_HomingProjectile::CreateHomingProjectile(UGameplayAbility* OwningAbility,
	const FName TaskInstanceName, const FGameplayTag& InWeaponTag, const TSubclassOf<AProjectileHoming>& InProjectileClass, UWeaponManager* InWeaponManager)
{
	UAbilityTask_HomingProjectile* HomingProjectileTask = NewAbilityTask<UAbilityTask_HomingProjectile>(OwningAbility, TaskInstanceName);
	HomingProjectileTask->Initialize_Internal(OwningAbility,InWeaponTag, InProjectileClass, InWeaponManager);	
	return HomingProjectileTask;
}

void UAbilityTask_HomingProjectile::Initialize_Internal(const UGameplayAbility* OwningAbility,
	const FGameplayTag& InWeaponTag, const TSubclassOf<AProjectileHoming>& InProjectileClass, UWeaponManager* InWeaponManager)
{
	WeaponTag = InWeaponTag;
	ProjectileClass = InProjectileClass;
	WeaponManager = InWeaponManager;
	if (Ability)
	{
		UE_LOG(LogTemp, Display, TEXT("HomingProjectile::Initialize_Internal"));
	}

	auto Ac = GetAvatarActor();
	auto Root = GetAvatarActor()->GetRootComponent();
	GetAvatarActor()->Modify();
	TargetingSphere = NewObject<USphereComponent>(GetAvatarActor(),"TargetingSphere");	
	TargetingSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TargetingSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	TargetingSphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	TargetingSphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	TargetingSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TargetingSphere->OnComponentCreated();
	TargetingSphere->SetupAttachment(GetAvatarActor()->GetRootComponent());
	TargetingSphere->RegisterComponent();
	GetAvatarActor()->AddInstanceComponent(TargetingSphere);
	TargetingSphere->bHiddenInGame = true;

	FVector2D Viewport = FVector2D::ZeroVector;
	GEngine->GameViewport->GetViewportSize(Viewport);

	DefaultTargetingRadius = FMath::Max(Viewport.X, Viewport.Y);
	TargetingSphere->SetSphereRadius(DefaultTargetingRadius);
	UE_LOG(LogTemp, Display, TEXT("HomingProjectile::Initialize_Internal The DefaultRadius set is:: %f"), DefaultTargetingRadius);
	TargetingSphere->OnComponentBeginOverlap.AddDynamic(this, &UAbilityTask_HomingProjectile::OnTargetingSphereOverlap);

	const FWeaponInfo& Weapon = WeaponManager->GetCachedWeapon(InWeaponTag).GetValue();
	WeaponAttributeSet = Weapon.AttributeSet.Get();
	// get speed and other required variables and store them in variables declared in this class.
	ProjectilesToSpawn = WeaponAttributeSet->GetAmount();
	UE_LOG(LogTemp, Display, TEXT("HomingProjectile::Initialize_Internal ProjectilesToSpawn are %f"), WeaponAttributeSet->GetAmount());	
	
	TargetingRadiusCurveTable = LoadObject<UCurveTable>(this, TEXT("/Game/Blueprints/AbilitySystem/Abilities/Weapons/ProjectileHoming/CT_TargetingRadius.CT_TargetingRadius"));
	UpdateTargetingSphereRadius();
}

void UAbilityTask_HomingProjectile::SpawnProjectile()
{
	// reset the # of projectiles on every fire.
	ProjectileCount = ProjectilesToSpawn;

	if (ProjectileCount > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(ProjectileSpawnTimerHandle,this,&UAbilityTask_HomingProjectile::SpawnProjectile_Internal,
			WeaponAttributeSet->GetProjectileInterval(), true, 0.0f);
	}	
}

void UAbilityTask_HomingProjectile::SpawnProjectile_Internal()
{
	if (Ability !=nullptr && ProjectileClass != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = Cast<APawn>(GetAvatarActor());
		SpawnParams.Owner = GetAvatarActor();

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(GetAvatarActor()->GetActorLocation());

		AProjectileHoming* SpawnedProjectile = GetWorld()->SpawnActorDeferred<AProjectileHoming>(
			ProjectileClass,
			SpawnTransform,
			GetAvatarActor(),
			Cast<APawn>(GetAvatarActor()),
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

		// TODO set projectile speed and block by walls here;
		bool bIsBlockedByWalls = WeaponAttributeSet->GetBlockByWalls() == 1.0f?true:false;
		SpawnedProjectile->Initialize(bIsBlockedByWalls, WeaponAttributeSet->GetSpeed(), WeaponAttributeSet->GetPierce(),
			WeaponAttributeSet->GetDamage(), WeaponAttributeSet->GetArea(), FindClosestTarget(), GetAvatarActor());		
		SpawnedProjectile->FinishSpawning(SpawnTransform);

		ProjectileCount--;
		if (ProjectileCount <= 0)
		{
			GetWorld()->GetTimerManager().ClearTimer(ProjectileSpawnTimerHandle);
		}
	}
}

void UAbilityTask_HomingProjectile::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
}

const AActor* UAbilityTask_HomingProjectile::FindClosestTarget() const
{
	const FVector ActorLocation = GetAvatarActor()->GetActorLocation();

	// If no closest enemy found then shoot in the direction of player facing and as far as possible
	const AActor* ClosestTarget = nullptr;
	
	// Some random max initial value.
	float DistanceSquared = 1000000.0f;
	
	// Need to export an array so that we get a copy to work on in case new enemies are added by the overlap
	// function while this function is executing.
	TArray<AActor*> Targets = HitTargets.Array();
	for (const AActor* Target : Targets)
	{
		const float DistSqd = FVector::DistSquared(ActorLocation, Target->GetActorLocation());
		if ( DistSqd < DistanceSquared)
		{
			DistanceSquared = DistSqd;
			ClosestTarget = Target;
		}
	}
	
	return ClosestTarget;
}

void UAbilityTask_HomingProjectile::OnTargetingSphereOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (const ICharacterBaseInterface* CharacterInterface = Cast<ICharacterBaseInterface>(OtherActor))
	{
		const FGameplayTag Tag = CharacterInterface->GetCharacterTag();
		if (Tag.ToString().Contains("Enemy"))
		{
			HitTargets.Add(OtherActor);
		}		
	}

	UpdateTargetingSphereRadius();
}

void UAbilityTask_HomingProjectile::UpdateTargetingSphereRadius() const
{
	if (TargetingRadiusCurveTable)
	{
		const int32 NumberOfEnemies = HitTargets.Num();
		if (NumberOfEnemies%5 == 0)
		{
			FString RowName;
			WeaponTag.ToString().Split(TEXT("."), nullptr, &RowName, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
		
			const FRealCurve* Curve = TargetingRadiusCurveTable->FindCurve(*RowName,
																		   FString::Printf(TEXT("Could not find RowName: %s in CurveTable: %s"), *RowName, TEXT("CT_ProjectileHoming")),
																		   true);


			const float Radius = DefaultTargetingRadius * Curve->Eval(NumberOfEnemies, 1.0f);
			//UE_LOG(LogTemp, Log, TEXT("UAbilityTask_HomingProjectile::UpdateTargetingSphereRadius The new Radius is:: %f"), Radius);
			TargetingSphere->SetSphereRadius(Radius);
		}
	}
	else
	{		
		TargetingSphere->SetSphereRadius(DefaultTargetingRadius);
		//UE_LOG(LogTemp, Log, TEXT("UAbilityTask_HomingProjectile::UpdateTargetingSphereRadius ELSE"));
	}
}

void UAbilityTask_HomingProjectile::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}
