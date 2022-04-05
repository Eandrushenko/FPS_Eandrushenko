// Fill out your copyright notice in the Description page of Project Settings.

#include "TimedTarget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameEngine.h"
#include "FPSGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "InGameHUD.h"


// Sets default values()
ATimedTarget::ATimedTarget()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATimedTarget::BeginPlay()
{
	Super::Super::BeginPlay();

	//Self Destroys after a variable amount of time
	SetLifeSpan(LifeSpan);
}

void ATimedTarget::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("I Just hit: %s"), *OtherActor->GetName()));

			////Update Score to reflect a successful hit
			UFPSGameInstance *GI = Cast<UFPSGameInstance>(GetGameInstance());
			if (GI->StartSpline)
			{
				GI->ridescore += 1;
			}

			AInGameHUD *InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

			if (InGameHUD)
			{
				InGameHUD->UpdateRide(GI->ridescore);
			}

			Destroy();
		}
	}
}
