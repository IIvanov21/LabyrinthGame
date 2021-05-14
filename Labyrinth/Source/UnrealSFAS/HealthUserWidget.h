// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthUserWidget.generated.h"

/**
 * User widget for the Health bar
 */
UCLASS()
class UNREALSFAS_API UHealthUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
			float Health=1.0f;
		UFUNCTION()
			void SetHealth(float HealthAmount);
	
};
