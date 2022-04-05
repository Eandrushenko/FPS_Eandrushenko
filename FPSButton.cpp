// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSButton.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/GameEngine.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "FPS_EandrushenkoCharacter.h"

// Sets default values
AFPSButton::AFPSButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create a 3D object to represent the physical target
	PanelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VMesh"));
	RootComponent = PanelMesh;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PMesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded())
	{
		PanelMesh->SetStaticMesh(CubeVisualAsset.Object);
		PanelMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		PanelMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		PanelMesh->SetWorldScale3D(FVector(0.1f, 0.4f, 0.4f));

		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(75.0f, 0.0f, 25.0f));
		VisualMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		VisualMesh->SetWorldScale3D(FVector(0.05f, 0.2f, 0.2f));
	}

	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Sphere Component"));
	TriggerSphere->InitSphereRadius(1500.0f);
	TriggerSphere->SetCollisionProfileName(TEXT("Trigger"));
	TriggerSphere->SetupAttachment(RootComponent);

	isNear = false;

	TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AFPSButton::OnOverlapBegin);
	TriggerSphere->OnComponentEndOverlap.AddDynamic(this, &AFPSButton::OnOverlapEnd);

	isPressed = false;
}

// Called when the game starts or when spawned
void AFPSButton::BeginPlay()
{
	Super::BeginPlay();

	//PrimaryActorTick.SetTickFunctionEnable(false);
}

// Called every frame
void AFPSButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPressed && isNear)
	{
		//if (GEngine)
		//	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Silver, player->GetName());

		VisualMesh->SetRelativeLocation(FVector(35.0f, 0.0f, 25.0f));
	}
	else
	{
		VisualMesh->SetRelativeLocation(FVector(75.0f, 0.0f, 25.0f));
	}
}


void AFPSButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		if (OtherActor->GetClass()->ImplementsInterface(UButtonInterface::StaticClass()))
		{
			isNear = true;
			isPressed = IButtonInterface::Execute_Interact(OtherActor);
		}
		else
		{
			isPressed = false;
		}
	}
}

void AFPSButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor != this)
	{
		isNear = false;
		VisualMesh->SetRelativeLocation(FVector(75.0f, 0.0f, 25.0f));
		isPressed = false;
	}
}
