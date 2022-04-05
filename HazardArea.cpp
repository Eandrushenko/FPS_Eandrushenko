// Fill out your copyright notice in the Description page of Project Settings.

#include "HazardArea.h"
#include "DrawDebugHelpers.h"
#include "Engine/GameEngine.h"
#include "GameFramework/Controller.h"

AHazardArea::AHazardArea()
{
	OnActorBeginOverlap.AddDynamic(this, &AHazardArea::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AHazardArea::OnOverlapEnd);
}

void AHazardArea::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Red, true, -1, 0, 5);
}

void AHazardArea::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *OverlappedActor->GetName());

	}

	//Spawn a new player character at RespawnLocation, unposses old player character, posses new player character, destroy the old player character
	if (OtherActor)
	{
		AFPS_EandrushenkoCharacter *player = Cast<AFPS_EandrushenkoCharacter>(OtherActor);

		if (RespawnLocation)
		{
			const FRotator SpawnRotation = RespawnLocation->GetActorRotation();
			const FVector SpawnLocation = RespawnLocation->GetActorLocation();

			AFPS_EandrushenkoCharacter *NewSpawn = GetWorld()->SpawnActor<AFPS_EandrushenkoCharacter>(CharacterBP, SpawnLocation, SpawnRotation);

			AController* SavedController = player->GetController();

			SavedController->UnPossess();

			SavedController->Possess(Cast<AFPS_EandrushenkoCharacter>(NewSpawn));

			OtherActor->Destroy();

		}

	}
}

void AHazardArea::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *OtherActor->GetName());
	}
}

