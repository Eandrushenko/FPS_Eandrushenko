// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "PressurePlate.generated.h"

/**
 * 
 */
UCLASS()
class FPS_EANDRUSHENKO_API APressurePlate : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	
	virtual void BeginPlay() override;

public:

	APressurePlate();

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void MoveWall();
	
	//Assign any wall or actor that you want to be moved on the z-axis
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = OnBoarding)
	AActor *TargetActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float height = 450.0f;
	
};
