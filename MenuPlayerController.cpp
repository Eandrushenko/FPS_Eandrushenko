// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuPlayerController.h"
#include "FPS_EandrushenkoHUD.h"
#include "Kismet/GameplayStatics.h"


AMenuPlayerController::AMenuPlayerController()
{

}

void AMenuPlayerController::ChangeLevel()
{
	if (AFPS_EandrushenkoHUD *MenuHUD = Cast<AFPS_EandrushenkoHUD>(GetHUD()))
	{
		UGameplayStatics::OpenLevel(GetWorld(), "Level1");
	}
}

