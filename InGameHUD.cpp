// Fill out your copyright notice in the Description page of Project Settings.

#include "InGameHUD.h"

AInGameHUD::AInGameHUD()
{

}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreWidgetClass)
	{
		ScoreWidget = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);
		if (ScoreWidget)
		{
			ScoreWidget->AddToViewport();
		}
	}
}

void AInGameHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AInGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AInGameHUD::UpdateScore(int32 Value, int32 Score)
{
	if (ScoreWidget)
	{
		ScoreWidget->UpdateScore(Value, Score);
	}
}

void AInGameHUD::UpdateRide(int32 Value)
{
	if (ScoreWidget)
	{
		ScoreWidget->UpdateRide(Value);
	}
}

void AInGameHUD::UpdateHighScore(int32 Value)
{
	if (ScoreWidget)
	{
		ScoreWidget->UpdateHighScore(Value);
	}
}
