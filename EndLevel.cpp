// Fill out your copyright notice in the Description page of Project Settings.

#include "EndLevel.h"
#include "DrawDebugHelpers.h"
#include "Engine/GameEngine.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameInstance.h"


AEndLevel::AEndLevel()
{
	OnActorBeginOverlap.AddDynamic(this, &AEndLevel::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AEndLevel::OnOverlapEnd);
}

void AEndLevel::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Blue, true, -1, 0, 5);
}

void AEndLevel::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, *OverlappedActor->GetName());

		//Check if score is met then reset Gameinstance Variables and go to MainMenu level
		if (Check())
		{
			UFPSGameInstance *GI = Cast<UFPSGameInstance>(GetGameInstance());

			GI->score = 0;
			GI->count = 0;

			UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
		}
	}
}

void AEndLevel::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, *OtherActor->GetName());
	}
}

//Returns a bool to see if all targets have been hit
bool AEndLevel::Check()
{
	bool result = false;

	UFPSGameInstance *GI = Cast<UFPSGameInstance>(GetGameInstance());

	if (GI->score >= GI->count)
	{
		result = true;
	}

	return result;
}