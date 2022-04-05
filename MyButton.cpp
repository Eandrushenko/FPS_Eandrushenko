// Fill out your copyright notice in the Description page of Project Settings.

#include "MyButton.h"
#include "DrawDebugHelpers.h"
#include "Engine/GameEngine.h"
#include "FPSGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"




AMyButton::AMyButton()
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
		VisualMesh->SetRelativeLocation(FVector(-30.0f, 0.0f, 0.0f));
		VisualMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		VisualMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		VisualMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	}

	OnActorBeginOverlap.AddDynamic(this, &AMyButton::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMyButton::OnOverlapEnd);

	isNear = false;
}


void AMyButton::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Silver, true, -1, 0, 5);
}

void AMyButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (player)
	{
		if (player->isUsing && isNear)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Silver, player->GetName());
		}
	}


}

void AMyButton::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		if (Cast<AFPS_EandrushenkoCharacter>(OtherActor))
		{
			isNear = true;
			player = Cast<AFPS_EandrushenkoCharacter>(OtherActor);
		}
	}
}

void AMyButton::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && OtherActor != this)
	{
		isNear = false;
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Silver, *OtherActor->GetName());
	}
}

