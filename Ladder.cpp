// Fill out your copyright notice in the Description page of Project Settings.

#include "Ladder.h"
#include "Engine/GameEngine.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "FPS_EandrushenkoCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ALadder::ALadder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a physical object to represent the ladder
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		VisualMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		VisualMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		VisualMesh->SetWorldScale3D(FVector(0.06f, 1.0f, 3.0f));
	}

	//Handle Overlap functions
	OnActorBeginOverlap.AddDynamic(this, &ALadder::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &ALadder::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ALadder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALadder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALadder::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if ((OtherActor != NULL) && (OtherActor != this))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::Printf(TEXT("I Just hit: %s"), *OtherActor->GetName()));
		}
		
		//If the player is touching the ladder, overwrite controls to allow the player to climb the ladder
		if (Cast<AFPS_EandrushenkoCharacter>(OtherActor))
		{
			AFPS_EandrushenkoCharacter *player = Cast<AFPS_EandrushenkoCharacter>(OtherActor);
			UCharacterMovementComponent *MovementPtr = Cast<UCharacterMovementComponent>(player->GetCharacterMovement());
			MovementPtr->SetMovementMode(EMovementMode::MOVE_Flying);
		}
	}
}

void ALadder::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if ((OtherActor != NULL) && (OtherActor != this))
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::Printf(TEXT("I Just hit: %s"), *OtherActor->GetName()));
		}
		
		//Return to player default state when the player is no longer touching the ladder
		if (Cast<AFPS_EandrushenkoCharacter>(OtherActor))
		{
			AFPS_EandrushenkoCharacter *player = Cast<AFPS_EandrushenkoCharacter>(OtherActor);
			UCharacterMovementComponent *MovementPtr = Cast<UCharacterMovementComponent>(player->GetCharacterMovement());
			MovementPtr->SetMovementMode(EMovementMode::MOVE_Walking);
		}
}
