// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime//UMG/Public/UMG.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_EANDRUSHENKO_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UScoreWidget(const FObjectInitializer &ObjectInitializer);

	virtual void NativeConstruct() override;

	void UpdateScore(int32 score, int32 count);

	void UpdateRide(int32 score);

	void UpdateHighScore(int32 score);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock *ScoreText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock *RideScore;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock *HighScore;
};
