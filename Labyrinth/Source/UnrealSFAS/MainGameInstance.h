// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * Game instance class to help save progress across multiple Levels.
 */
UCLASS()
class UNREALSFAS_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMainGameInstance(const FObjectInitializer& ObjectInitializer);
	/*
	 * All the data needed to be saved across levels.
	 */
	UPROPERTY(EditAnywhere)
		float Time;
	UPROPERTY(EditAnywhere)
		float Score;
	UPROPERTY(EditAnywhere)
		float Health;
	UPROPERTY(EditAnywhere)
		bool KeyOne;
	UPROPERTY(EditAnywhere)
		bool KeyTwo;
	UPROPERTY(EditAnywhere)
		bool KeyThree;
	UPROPERTY(EditAnywhere)
		bool KeysCollected;
	/*
	 * Reseter when the player starts a new game.
	 */
	UFUNCTION()
		void ResetStats();
};
