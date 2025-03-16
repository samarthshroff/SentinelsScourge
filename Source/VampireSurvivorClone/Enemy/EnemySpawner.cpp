// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "EnemyCharacterBase.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// CurrentLevelName = GetWorld()->GetMapName();
 //
	// FString Path = FPaths::ProjectContentDir();
	// Path.Append("DataTables/");
	// Path.Append("DT_");
	// Path.Append(CurrentLevelName);
	// Path.Append(".");
	// Path.Append("DT_");
	// Path.Append(CurrentLevelName);
 //    UE_LOG(LogTemp, Log, TEXT("The Path is %s"), *(Path));
	
	
	//static ConstructorHelpers::FObjectFinder<UDataTable> CurrentLevelDataTable(TEXT("/Game/DataTables/DT_Level1.DT_Level1"))
}

AEnemySpawner::~AEnemySpawner()
{
	EnemiesDataForCurrentLevel.Empty();
	StartSeconds.Empty();
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));	
	PlayerCharacterScale = PlayerCharacter->GetActorScale();
	
	// /Game/DataTables/DT_Level1.DT_Level1
	CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	FString Path = "/Game/";
	Path.Append("DataTables/");
	Path.Append("DT_");
	Path.Append(CurrentLevelName);
	Path.Append(".");
	Path.Append("DT_");
	Path.Append(CurrentLevelName);
	UE_LOG(LogTemp, Log, TEXT("The Path is %s"), *(Path));

	TSoftObjectPtr<UDataTable> CurrentDataTable = TSoftObjectPtr<UDataTable>(FSoftObjectPath (Path));
	if (CurrentDataTable == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Could not load DataTable"));
	}
	if (!CurrentDataTable.IsValid())
	{
		FStreamableManager& Manager = UAssetManager::GetStreamableManager();
		UObject* DataTable = Manager.LoadSynchronous(CurrentDataTable.ToSoftObjectPath());
		if (UDataTable* LoadedDataTable = Cast<UDataTable>(DataTable))
		{
			ProcessDataTable(LoadedDataTable);
		}			
	}
	else
	{
		UDataTable* LoadedDataTable = Cast<UDataTable>(CurrentDataTable.Get());
		ProcessDataTable(LoadedDataTable);
	}		
}

void AEnemySpawner::ProcessDataTable(UDataTable* DataTable)
{
	FString ContextString = "Could not find any rows in the datatable";
	TArray<FEnemyMetaData*> EnemiesData;
	DataTable->GetAllRows(ContextString, EnemiesData);

	UE_LOG(LogTemp, Log, TEXT("EnemiesData count is %d"), EnemiesData.Num());
	for (FEnemyMetaData* MetaData : EnemiesData)
	{
		TObjectPtr<UEnemyData> Data = NewObject<UEnemyData>();
		
		FGameplayTag EnemyTag = MetaData->EnemyTag;
		EnemiesDataForCurrentLevel.Add(EnemyTag, MoveTemp(Data));		
		EnemiesDataForCurrentLevel[EnemyTag]->OnAssetsLoaded.BindLambda([&](const FGameplayTag& Tag, double 
		SpawnIntervalInSeconds)
		{
			if (!EnemiesDataForCurrentLevel.Contains(Tag))
			{
				UE_LOG(LogTemp, Warning, TEXT("Invalid tag: %s"), *(Tag.ToString()));
				return;
			}
			//UE_LOG(LogTemp, Log, TEXT("Assets loaded for %s"), *(Tag.ToString()));
			StartSeconds.Add(Tag, TTuple<double, double>(GetWorld()->GetTimeSeconds(), SpawnIntervalInSeconds));
			//UE_LOG(LogTemp, Log, TEXT("tag is %s and value is %s"), *(Tag.ToString()), *(EnemiesDataForCurrentLevel[Tag]->SkeletalMesh->GetPathName()));
		});

		EnemiesDataForCurrentLevel[EnemyTag]->Initialize(MetaData);
	}
	//UE_LOG(LogTemp, Log, TEXT("EnemiesDataForCurrentLevel count is %d"), EnemiesDataForCurrentLevel.Num());
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (const TTuple<FGameplayTag, TTuple<double, double>> Timer : StartSeconds)
	{
		const FGameplayTag& Tag = Timer.Key;
		if (GetWorld()->GetTimeSeconds() - Timer.Value.Key >= Timer.Value.Value)
		{
			const auto EnemyData = EnemiesDataForCurrentLevel[Tag].Get();
			// Spawn this enemy type only when it's skeletal mesh and anim instance are loaded into memory.
			if (!EnemyData->IsLoaded) continue;

			if (const auto MetaData = EnemyData->MetaData.Get())
			{
				StartSeconds[Tag] = TTuple<double, double>(GetWorld()->GetTimeSeconds(), MetaData->SpawnIntervalInSeconds);
				
				if (EnemyData->SkeletalMesh != nullptr)
				{
					FVector PlayerLocation = PlayerCharacter->GetActorLocation();
					const auto Angle = FMath::FRandRange(-360.0f,360.0f);
					const auto VectorMagnitude = 400.0f;//FMath::FRandRange(MetaData->MinimumSpawnDistanceFromPlayer,MetaData->MaximumSpawnDistanceFromPlayer);
					
					FVector SpawnLocation = FVector(PlayerCharacter->GetActorForwardVector()*VectorMagnitude);
					FQuat RotationQuat(FVector::UpVector, FMath::DegreesToRadians(Angle));
					SpawnLocation = RotationQuat.RotateVector(SpawnLocation);
					SpawnLocation.Z = PlayerLocation.Z;
					/*UE_LOG(LogTemp, Log, TEXT("The Angle in Deg is %f FMath::DegreesToRadians(Angle) %f PlayerLocation %s and EndVector is %s player forward vector %s player forward vector rotation %s"),
						Angle, FMath::DegreesToRadians(Angle),
						*PlayerLocation.ToString(), *EndVector.ToString(), *PlayerCharacter->GetActorForwardVector().ToString(), *PlayerCharacter->GetActorForwardVector().Rotation().ToString());
					
					DrawDebugLine(GetWorld(), PlayerLocation, EndVector,	FColor::Red, true, 1000.0f, 0, 2.0f);*/
					
					// //FQuat RotationQuat(FVector::UpVector, Angle);
					// //UE_LOG(LogTemp, Log, TEXT("The Angle in Deg is %f Angle in Rad is %f and RotationQuat is %s"), AD, Angle, *RotationQuat.ToString());
					//
					// // DrawDebugLine(GetWorld(), PlayerCharacterForwardVectorAtStart, FVector(PlayerLocation.X-500.0f,PlayerLocation.Y,PlayerLocation.Z),
					// // FColor::Red, true, 1000.0f, 0, 2.0f);
					// //FVector SpawnLocation = RotationQuat.RotateVector(PlayerLocation);
					//
					// FVector SpawnLocation = PlayerLocation.GetSafeNormal()*VectorMagnitude;
					// float X = FMath::Cos(Angle)*SpawnLocation.X - FMath::Sin(Angle)*SpawnLocation.Y;
					// float Y = FMath::Sin(Angle)*SpawnLocation.X + FMath::Cos(Angle)*SpawnLocation.Y;
					// SpawnLocation.X = X;
					// SpawnLocation.Y = Y;
					// SpawnLocation.Z = PlayerLocation.Z;
					//
					// // DrawDebugLine(GetWorld(), SpawnLocation,FVector(SpawnLocation.X-500.0f,SpawnLocation.Y,SpawnLocation.Z),
					// // 				FColor::Blue,true,1000.0f,0,2.0f);
					//
					//
					//
					// // DrawDebugLine(GetWorld(), SpawnLocation,FVector(SpawnLocation.X-500.0f,SpawnLocation.Y,SpawnLocation.Z),
					// // 				FColor::Blue,true,1000.0f,0,2.0f);
					//
					// SpawnLocation *= VectorMagnitude;
					// SpawnLocation.Z = PlayerLocation.Z;
					//
					//
					// Look at the player
					const float dX = PlayerLocation.X - SpawnLocation.X;
					const float dY = PlayerLocation.Y - SpawnLocation.Y;
					float YawInRadians = FMath::Atan2(dY, dX);
					float YawInDegrees = FMath::RadiansToDegrees(YawInRadians);
					FRotator SpawnRotation = FRotator::ZeroRotator;// FRotator(0.0f,YawInDegrees, 0.0f);
					
					FTransform SpawnTransform (SpawnRotation, SpawnLocation, PlayerCharacterScale);					
					const auto TempEnemy = Cast<AEnemyCharacterBase>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), 
					AEnemyCharacterBase::StaticClass(), SpawnTransform));
						//GetWorld()->SpawnActor<AEnemyCharacterBase>(AEnemyCharacterBase::StaticClass(), SpawnTransform);
					
					TempEnemy->UpdateProperties(MetaData->EnemyTag, MetaData->Speed, MetaData->Health, MetaData->Damage,
						MetaData->DistanceFromPlayerCharacter, MetaData->WeaponType,
						EnemyData->AnimInstance, EnemyData->SkeletalMesh, PlayerCharacter->GetMesh()->GetRelativeScale3D());
					
					UGameplayStatics::FinishSpawningActor(TempEnemy, SpawnTransform);
				}
			}
		}
	}
}

