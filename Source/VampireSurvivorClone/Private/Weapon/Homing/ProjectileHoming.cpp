// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Homing/ProjectileHoming.h"


#include "GameplayTagContainer.h"
#include "Character/CharacterBaseInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileHoming::AProjectileHoming()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectileHoming::OnSphereOverlap);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");
	ProjectileMovement->InitialSpeed = 550.0f;
	ProjectileMovement->MaxSpeed = 550.0f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AProjectileHoming::BeginPlay()
{
	Super::BeginPlay();	
}

void AProjectileHoming::Initialize(const bool InbBlockedByWalls, const float InSpeed, const float InPierce, const float InDamage, const TObjectPtr<AActor> InHomingTargetActor)
{
	bIsBlockedByWalls = InbBlockedByWalls;
	Speed = InSpeed;
	Pierce = InPierce;
	Damage = InDamage;
	PierceCount = 0;
	HomingTargetActor = InHomingTargetActor;

	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
}

void AProjectileHoming::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr && OtherActor == HomingTargetActor)
	{
		Destroy();
	}
}

void AProjectileHoming::Activate()
{
	IWeaponCategoryInterface::Activate();
}

void AProjectileHoming::DeActivate()
{
	IWeaponCategoryInterface::DeActivate();
}

void AProjectileHoming::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (HomingTargetActor != nullptr)
	{
		const FVector TargetLocation = HomingTargetActor->GetActorLocation();
		const FVector CurrentLocation = GetActorLocation();
		const FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	
		if (bIsBlockedByWalls)
		{
			FHitResult Hit;
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(this);
			if (AvatarActor != nullptr)	Params.AddIgnoredActor(AvatarActor);
	
			if (GetWorld()->LineTraceSingleByChannel(Hit, CurrentLocation, TargetLocation, ECC_Visibility, Params))
			{
				if (Hit.GetActor() != HomingTargetActor)
				{
					return;
				}
			}
		}

		constexpr float HomingStrength = 5.0f;
		const FVector CurrentVelocity = ProjectileMovement->Velocity;
		const FVector TargetVelocity  = Direction * CurrentVelocity.Size();
	
		ProjectileMovement->Velocity = FMath::VInterpTo(CurrentVelocity, TargetVelocity, DeltaSeconds, HomingStrength);
		// Look at the player
		const float dX = TargetLocation.X - CurrentLocation.X;
		const float dY = TargetLocation.Y - CurrentLocation.Y;
		float YawInRadians = FMath::Atan2(dY, dX);
		float YawInDegrees = FMath::RadiansToDegrees(YawInRadians);
		FRotator SpawnRotation = FRotator(0.0f,YawInDegrees, 0.0f);
		SetActorRotation(SpawnRotation);
	}
}
