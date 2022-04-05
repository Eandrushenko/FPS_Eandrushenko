// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ScoreWidget.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class FPS_EANDRUSHENKO_API AInGameHUD : public AHUD
{
	GENERATED_BODY()
	
public:

	AInGameHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	void UpdateScore(int32 Value, int32 Score);

	UFUNCTION()
	void UpdateRide(int32 Value);

	UFUNCTION()
	void UpdateHighScore(int32 Value);

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> ScoreWidgetClass;

private:

	UScoreWidget *ScoreWidget;

};
