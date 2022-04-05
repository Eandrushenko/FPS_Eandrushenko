// Fill out your copyright notice in the Description page of Project Settings.

#include "TargetReset.h"
#include "DrawDebugHelpers.h"
#include "Engine/GameEngine.h"
#include "FPSGameInstance.h"



ATargetReset::ATargetReset()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OnActorBeginOverlap.AddDynamic(this, &ATargetReset::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ATargetReset::OnOverlapEnd);
}


void ATargetReset::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Orange, true, -1, 0, 5);
}

void ATargetReset::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, *OverlappedActor->GetName());

		//Make all targets visible and interactable once again
		for (AActor* Actor : TargetArray)
		{
			Actor->SetActorTickEnabled(true);
			Actor->SetActorHiddenInGame(false);
			Actor->SetActorEnableCollision(true);
		}

		//Reset Score to 0
		UFPSGameInstance *GI = Cast<UFPSGameInstance>(GetGameInstance());
		GI->score = 0;

		AInGameHUD *InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

		if (InGameHUD)
		{
			InGameHUD->UpdateScore(GI->score, GI->count);
		}
	}
}

void ATargetReset::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, *OtherActor->GetName());
	}
}



