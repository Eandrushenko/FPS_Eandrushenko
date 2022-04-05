// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FPSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPS_EANDRUSHENKO_API UFPSGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFPSGameInstance();

	//Number of Targets Hit
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 score;

	//Total Number of Targets in Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 count;

	//Spline Activation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StartSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ridescore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 highscore;
};
