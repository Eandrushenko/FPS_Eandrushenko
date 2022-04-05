// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"
#include "Engine/World.h"
#include "FPSGameInstance.h"
#include "InGameHUD.h"
#include "FPSButton.h"
#include "Engine/GameEngine.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	canMoveActor = false;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(Root);
	Spline->bDrawDebug = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	GI = Cast<UFPSGameInstance>(GetGameInstance());

	if (ActorToMoveClass)
	{
		ActorToMove = GetWorld()->SpawnActor<AActor>(ActorToMoveClass, Spline->GetComponentTransform());
		if (ActorToMove)
		{
			canMoveActor = false;
		}
	}

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (button)
	{
		if (button->isPressed)
		{
			GI->StartSpline = true;
		}

	}

	//Read Gameinstance variable, StartSpline, to see if Actor should be moving
	if (GI)
	{
		canMoveActor = GI->StartSpline;
	}

	if (ActorToMove && canMoveActor)
	{
		//Find our current position along the spline, on a 0-1 scale
		float CurrentSplineProgress = (GetWorld()->GetTimeSeconds() - StartTime) / Spline->Duration;

		float Distance = Spline->GetSplineLength() * CurrentSplineProgress;

		//Update Actor's Position
		FVector Position = Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);

		ActorToMove->SetActorLocation(Position);

		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Current Spline Progress: %f"), CurrentSplineProgress));

		//Get to the End of the Loop
		if (CurrentSplineProgress >= 1.0f)
		{
			GI->StartSpline = false;

			//Update HUD
			AInGameHUD *InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

			//Check for new high score
			if (GI->ridescore > GI->highscore)
			{
				GI->highscore = GI->ridescore;

				if (InGameHUD)
				{
					InGameHUD->UpdateHighScore(GI->highscore);
				}
			}

			//Reset Current Score
			InGameHUD->UpdateRide(0);
			GI->ridescore = 0;
		}
	}
	else
	{
		//If the ride is not active then we need to keep track of when the StartTime will be, so that we can offset it in our CurrentSplineProgress calculation
		StartTime = GetWorld()->GetTimeSeconds();
	}

}

