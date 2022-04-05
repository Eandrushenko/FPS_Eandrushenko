// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "FPS_EandrushenkoCharacter.h"
#include "MyButton.generated.h"

/**
 * 
 */
UCLASS()
class FPS_EANDRUSHENKO_API AMyButton : public ATriggerBox
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

	AFPS_EandrushenkoCharacter *player;

	bool isNear;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AMyButton();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh = nullptr;

	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

};
