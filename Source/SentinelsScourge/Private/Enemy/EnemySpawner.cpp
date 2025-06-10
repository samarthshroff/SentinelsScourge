// Copyright (c) Samarth Shroff. All Rights Reserved.
// This work is protected under applicable copyright laws in perpetuity.
// Licensed under the CC BY-NC-ND 4.0 License. See LICENSE file for details.

#include "Enemy/EnemySpawner.h"
#include "Player/PlayerCharacter.h"
#include "Enemy/EnemyCharacterBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AEnemySpawner::~AEnemySpawner()
{
	EnemiesData.Empty();
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* LocalPlayerController = GetWorld()->GetFirstPlayerController();
	PlayerCharacter = Cast<APlayerCharacter>(LocalPlayerController->GetPawn());
	PlayerCharacterScale = PlayerCharacter->GetActorScale();
	PlayerCharacterMeshScale = PlayerCharacter->GetMesh()->GetRelativeScale3D();
	 
	ProcessDataTable(EnemiesInfo);
}

void AEnemySpawner::ProcessDataTable(UDataTable* DataTable)
{
	FString ContextString = "Could not find any rows in the datatable";
	TArray<FEnemyMetaData*> EnemiesMetaData;
	DataTable->GetAllRows(ContextString, EnemiesMetaData);

	//UE_LOG(LogTemp, Log, TEXT("EnemiesData count is %d"), EnemiesMetaData.Num());
	for (FEnemyMetaData* MetaData : EnemiesMetaData)
	{
		TObjectPtr<UEnemyData> Data = NewObject<UEnemyData>();
		
		Data->MetaData = MakeUnique<FEnemyMetaData>(*MetaData);		
		FGameplayTag EnemyTag = MetaData->EnemyTag;
		Data->StartTimeInSeconds = -1.0;
		EnemiesData.Add(EnemyTag, MoveTemp(Data));
	}

	EnemiesMetaData.Empty();
	// For a new run it is always 1.0
	InitializeEnemies(1.0f);
	PlayerCharacter->RegisterToHeroLevelAttributeChange<AEnemySpawner>(this, &AEnemySpawner::OnHeroPlayerLevelChanged);
}

void AEnemySpawner::OnHeroPlayerLevelChanged(const FOnAttributeChangeData& AttributeData)
{
	InitializeEnemies(AttributeData.NewValue);
}

void AEnemySpawner::InitializeEnemies(int32 HeroLevel)
{
	for (TTuple<FGameplayTag, TObjectPtr<UEnemyData>> DataTuple : EnemiesData)
	{
		FGameplayTag Tag = DataTuple.Key;
		TObjectPtr<UEnemyData> Data = DataTuple.Value;
		if (Data->MetaData->IntroduceFromHeroLevel > HeroLevel)
			continue;
		
		EnemiesData[Tag]->OnAssetsLoaded.BindLambda([&](const FGameplayTag& GameplayTag, double 
		SpawnIntervalInSeconds)
		{
			if (!EnemiesData.Contains(GameplayTag))
			{
				UE_LOG(LogTemp, Warning, TEXT("[AEnemySpawner::OnHeroPlayerLevelChanged] Invalid tag: %s"), *(Tag.ToString()));
				return;
			}
			EnemiesData[GameplayTag]->StartTimeInSeconds = GetWorld()->GetTimeSeconds();
		});
		
		EnemiesData[Tag]->Initialize();		
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (const TTuple<FGameplayTag, TObjectPtr<UEnemyData>>& DataTuple : EnemiesData)
	{		
		TObjectPtr<UEnemyData> Data = DataTuple.Value;

		if (!IsValid(Data))
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid UEnemyData for tag %s"), *DataTuple.Key.ToString());
			continue;
		}
		
		// UE_LOG(LogTemp, Warning, TEXT("GetWorld()->GetTimeSeconds() - Data->StartTimeInSeconds %f & Data->MetaData->SpawnIntervalInSeconds %f"),
		// 	(GetWorld()->GetTimeSeconds() - Data->StartTimeInSeconds), Data->MetaData->SpawnIntervalInSeconds);
		
		if ( Data->StartTimeInSeconds != -1 &&
			GetWorld()->GetTimeSeconds() - Data->StartTimeInSeconds >= Data->MetaData->SpawnIntervalInSeconds)
		{
			// Spawn this enemy type only when it's skeletal mesh and anim instance are loaded into memory.
			if (!Data->bIsLoaded) continue;
	
			if (FEnemyMetaData* MetaData = Data->MetaData.Get())
			{
				Data->StartTimeInSeconds = GetWorld()->GetTimeSeconds();

				if (Data->SkeletalMesh != nullptr)
				{
					const FVector PlayerLocation = PlayerCharacter->GetActorLocation();
					const float Angle = FMath::FRandRange(-360.0f,360.0f);
					const float VectorMagnitude = FMath::FRandRange(MetaData->MinimumSpawnDistanceFromPlayer,
					MetaData->MaximumSpawnDistanceFromPlayer);
					
					FVector SpawnLocation = FVector(PlayerCharacter->GetActorForwardVector() * VectorMagnitude);
					FQuat RotationQuat(FVector::UpVector, FMath::DegreesToRadians(Angle));
					SpawnLocation = RotationQuat.RotateVector(SpawnLocation);
					SpawnLocation.Z = PlayerLocation.Z;
	
					// Look at player happens from behaviour tree
					FRotator SpawnRotation = FRotator::ZeroRotator;
					
					FTransform SpawnTransform (SpawnRotation, SpawnLocation, PlayerCharacterScale);					
					const auto TempEnemy = Cast<AEnemyCharacterBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), 
					AEnemyCharacterBase::StaticClass(), SpawnTransform, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
					
					TempEnemy->UpdateProperties(MetaData->EnemyTag, MetaData->DistanceFromPlayerCharacter, PlayerCharacterMeshScale,
						Data->AnimInstance, Data->AnimMontageDie, Data->SkeletalMesh, Data->DefaultAttributeClass);
					
					UGameplayStatics::FinishSpawningActor(TempEnemy, SpawnTransform);
				}
			}
		}
	}
}

