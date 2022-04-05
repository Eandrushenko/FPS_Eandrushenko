// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RideManager.generated.h"

UCLASS()
class FPS_EANDRUSHENKO_API ARideManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARideManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle MemberTimerHandle;

	class UFPSGameInstance *GI;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Location where the new player will be spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SpawnLocation;

	//Get the blueprint of the playercharacter
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ATimedTarget> TargetBP;
	
	UFUNCTION()
	void Spawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isSpawning;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AFPS_EandrushenkoCharacter *player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float XRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float YRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZRange;
};
