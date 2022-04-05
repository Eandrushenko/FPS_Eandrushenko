// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class FPS_EANDRUSHENKO_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "CustomSpline")
	TSubclassOf<class AActor> ActorToMoveClass;

	class AActor* ActorToMove;

	bool canMoveActor;

	float StartTime;

	class UFPSGameInstance *GI;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CustomSpline")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CustomSpline")
	class USplineComponent* Spline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CustomSpline")
	class AFPSButton* button;
	
};
