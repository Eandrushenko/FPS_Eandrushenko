// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPS_EandrushenkoHUD.generated.h"

UCLASS()
class AFPS_EandrushenkoHUD : public AHUD
{
	GENERATED_BODY()

public:
	AFPS_EandrushenkoHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	void ShowMenu();
	void HideMenu();

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

protected:

	TSharedPtr<class SMainMenuWidget> MenuWidget;
	TSharedPtr<class SWidget> MenuWidgetContainer;

	virtual void BeginPlay() override;
};

