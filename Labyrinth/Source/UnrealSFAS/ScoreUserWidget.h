// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUserWidget.generated.h"

/**
 * Score UI widget. 
 */
UCLASS()
class UNREALSFAS_API UScoreUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		FString Score;
	UPROPERTY(EditAnywhere)
		int CurrentScore = 0;
	UFUNCTION()
		void UpdateScore(int Points);
};
