// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UButtonInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FPS_EANDRUSHENKO_API IButtonInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	bool Interact();
};
