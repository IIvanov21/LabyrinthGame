// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSFAS_API UKeyUserWidget : public UUserWidget
{
	GENERATED_BODY()
private:

	
public:
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		bool KeyState;
	UFUNCTION()
		void KeyCollected();
	
};
