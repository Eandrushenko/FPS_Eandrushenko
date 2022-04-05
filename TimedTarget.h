// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootingTarget.h"
#include "TimedTarget.generated.h"

UCLASS()
class FPS_EANDRUSHENKO_API ATimedTarget : public AShootingTarget
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimedTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingActor")
	float LifeSpan = 3.0f;
	
};
