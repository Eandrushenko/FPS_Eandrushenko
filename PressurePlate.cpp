// Fill out your copyright notice in the Description page of Project Settings.

#include "PressurePlate.h"
#include "DrawDebugHelpers.h"
#include "Engine/GameEngine.h"



APressurePlate::APressurePlate()
{
	OnActorBeginOverlap.AddDynamic(this, &APressurePlate::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &APressurePlate::OnOverlapEnd);
}

void APressurePlate::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Yellow, true, -1, 0, 5);
}

void APressurePlate::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *OverlappedActor->GetName());

		MoveWall();
	}
}

void APressurePlate::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *OtherActor->GetName());
	}
}

//Move an actor on the Z axis, a "height" amount of units
void APressurePlate::MoveWall()
{
	if (TargetActor)
	{
		FVector NewLocation = TargetActor->GetActorLocation();
		NewLocation.Z = height;
		TargetActor->SetActorLocation(NewLocation);
	}
}