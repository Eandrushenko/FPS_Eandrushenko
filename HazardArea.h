// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "FPS_EandrushenkoCharacter.h"
#include "HazardArea.generated.h"

/**
 * 
 */
UCLASS()
class FPS_EANDRUSHENKO_API AHazardArea : public ATriggerBox
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

public:

	AHazardArea();

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	//Location where the new player will be spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor *RespawnLocation;

	//Get the blueprint of the playercharacter
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AFPS_EandrushenkoCharacter> CharacterBP;

	
};
