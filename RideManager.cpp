// Fill out your copyright notice in the Description page of Project Settings.

#include "RideManager.h"
#include "InGameHUD.h"
#include "FPSGameInstance.h"
#include "TimerManager.h"
#include "FPS_EandrushenkoCharacter.h"
#include "TimedTarget.h"


// Sets default values
ARideManager::ARideManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnTime = 1.0f;
	isSpawning = false;

	XRange = 1000.0f;
	YRange = 1000.0f;
	ZRange = 200.0f;
}

// Called when the game starts or when spawned
void ARideManager::BeginPlay()
{
	Super::BeginPlay();

	GI = Cast<UFPSGameInstance>(GetGameInstance());

	AInGameHUD *InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (InGameHUD)
	{
		InGameHUD->UpdateRide(GI->ridescore);
		InGameHUD->UpdateHighScore(GI->highscore);
	}

	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ARideManager::Spawner, SpawnTime, true, 0.0f);
}

// Called every frame
void ARideManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Only spawn targets when riding along the spline
	isSpawning = GI->StartSpline;
	
}

//Repeating function for spawning actors around the player
void ARideManager::Spawner()
{
	if (GEngine && isSpawning && player && TargetBP)
	{
		float Xpos = player->GetTargetLocation().X + FMath::RandRange(-XRange, XRange);
		float Ypos = player->GetTargetLocation().Y + FMath::RandRange(-YRange, YRange);
		float Zpos = player->GetTargetLocation().Z + FMath::RandRange(-ZRange, ZRange);

		FVector SpawnLocation = FVector(Xpos, Ypos, Zpos);
		FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

		GetWorld()->SpawnActor<ATimedTarget>(TargetBP, SpawnLocation, SpawnRotation);
	}

}