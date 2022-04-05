// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootingTarget.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/GameEngine.h"
#include "FPSGameInstance.h"


// Sets default values()
AShootingTarget::AShootingTarget()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a 3D object to represent the physical target
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		VisualMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		VisualMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
	}

	//Handle OnHit function
	VisualMesh->OnComponentHit.AddDynamic(this, &AShootingTarget::OnHit);

}

// Called when the game starts or when spawned
void AShootingTarget::BeginPlay()
{
	Super::BeginPlay();

	UFPSGameInstance *GI = Cast<UFPSGameInstance>(GetGameInstance());
	GI->count += 1;

	AInGameHUD *InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	if (InGameHUD)
	{
		UFPSGameInstance *GI = Cast<UFPSGameInstance>(GetGameInstance());
		InGameHUD->UpdateScore(GI->score, GI->count);
	}
}

// Called every frame
void AShootingTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Make Target Hover and Spin
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * FloatSpeed;
	float DeltaRotation = DeltaTime * RotationSpeed;
	NewRotation.Yaw += DeltaRotation;
	SetActorLocationAndRotation(NewLocation, NewRotation);

}

void AShootingTarget::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("I Just hit: %s"), *OtherActor->GetName()));
			
			//Hide the Target when hit
			SetActorTickEnabled(false);
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);

			//Update Score to reflect a successful hit
			UFPSGameInstance *GI = Cast<UFPSGameInstance>(GetGameInstance());
			GI->score += 1;
	
			AInGameHUD *InGameHUD = Cast<AInGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
			if (InGameHUD)
			{
				InGameHUD->UpdateScore(GI->score, GI->count);
			}

			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Score: %d"), GI->score));
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::White, FString::Printf(TEXT("Count: %d"), GI->count));
		}
	}
}

