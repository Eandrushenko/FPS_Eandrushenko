// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSButton.generated.h"

UCLASS()
class FPS_EANDRUSHENKO_API AFPSButton : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPSButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool isNear;

	//class AFPS_EandrushenkoCharacter *player;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* VisualMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* PanelMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* TriggerSphere;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isPressed;
};