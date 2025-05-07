// Fill out your copyright notice in the Description page of Project Settings.
#include "VampireSurvivorClone/Public/Player/PlayerCharacterController.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Components/SplineComponent.h"

APlayerCharacterController::APlayerCharacterController()
{
	bShowMouseCursor = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void APlayerCharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AutoRun();	
}

void APlayerCharacterController::AutoRun()
{
	if (!bAutoRunning) return;
	
	APawn* ControlledPawn = GetPawn();
	if (!ControlledPawn) return;	

	const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(),	ESplineCoordinateSpace::World);
	const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,	ESplineCoordinateSpace::World);

	ControlledPawn->AddMovementInput(Direction);
	const FRotator SmoothRotation = FMath::RInterpTo(ControlledPawn->GetActorRotation(), Direction.Rotation(), GetWorld()
	->GetDeltaSeconds(), 10.0f);
	ControlledPawn->SetActorRotation(SmoothRotation);

	const float Distance = (LocationOnSpline - ClickedLocation).Length();
	if (Distance <= AutoRunAcceptanceRadius)
	{
		bAutoRunning = false;
	}
}

void APlayerCharacterController::MoveButtonHeld(const FInputActionValue& Value)
{
	FollowTime = GetWorld()->GetDeltaSeconds();
	
	// Move the player in the world to the mouse click location on screen
	// Get the world position of the mouse click.	
	if (FHitResult Result; GetHitResultUnderCursor(ECC_Visibility, false, Result))
	{
		ClickedLocation = Result.ImpactPoint;
	}

	// Get the direction from player to the mouse cursor.
	// Move the player in that direction.
	if (APawn* ControlledPawn = GetPawn())
	{		
		FVector DirectionVector = (ClickedLocation - ControlledPawn->GetActorLocation()).GetSafeNormal();
		DirectionVector.Z = 0.0f;
		if (!DirectionVector.IsNearlyZero())
		{
			ControlledPawn->AddMovementInput(DirectionVector);
			const FRotator SmoothRotation = FMath::RInterpTo(ControlledPawn->GetActorRotation(), DirectionVector.Rotation(), GetWorld()->GetDeltaSeconds(), 10.0f);
			ControlledPawn->SetActorRotation(SmoothRotation);
		}		
	}	
}

void APlayerCharacterController::MoveButtonPressed(const FInputActionValue& Value)
{
	bAutoRunning = false;
}

void APlayerCharacterController::MoveButtonReleased(const FInputActionValue& Value)
{
	if (const APawn* ControlledPawn = GetPawn(); ControlledPawn && FollowTime <= ShortPressThreshold)
	{
		FollowTime = 0.0f;
		// Get the Navpath to the mouse click location from the actor location and store each point as spline points.
		if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this,	ControlledPawn->GetActorLocation(),ClickedLocation))
		{
			Spline->ClearSplinePoints();
			for (FVector PathPoint : NavPath->PathPoints)
			{
				Spline->AddSplinePoint(PathPoint, ESplineCoordinateSpace::World);				
			}
			ClickedLocation = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
			bAutoRunning = true;
		}
	}
}
