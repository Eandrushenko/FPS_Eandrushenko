// Fill out your copyright notice in the Description page of Project Settings.

#include "ScoreWidget.h"

UScoreWidget::UScoreWidget(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
}

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

//Display the number of targets hit, over the total number of targets
void UScoreWidget::UpdateScore(int32 score, int32 count)
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d / %d Targets Hit"), score, count)));
	}
}

void UScoreWidget::UpdateRide(int32 score)
{
	if (RideScore)
	{
		RideScore->SetText(FText::FromString(FString::Printf(TEXT("Targets Hit: %d"), score)));
	}
}

void UScoreWidget::UpdateHighScore(int32 score)
{
	if (HighScore)
	{
		HighScore->SetText(FText::FromString(FString::Printf(TEXT("HighScore: %d"), score)));
	}
}