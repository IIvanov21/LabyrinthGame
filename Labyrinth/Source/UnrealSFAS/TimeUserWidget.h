// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSFAS_API UTimeUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		FString TimeDisplay;
	UFUNCTION()
		void GetTimer(int timerIn);
	UPROPERTY(EditAnywhere)
		int Minutes;
	UPROPERTY(EditAnywhere)
		int Seconds;
};
