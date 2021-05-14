// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeyUserWidget.generated.h"

/**
 * User widget to display the collected keys from each portal.
 */
class UMainGameInstance;
UCLASS()
class UNREALSFAS_API UKeyUserWidget : public UUserWidget
{
	GENERATED_BODY()
private:

	
public:
	UPROPERTY(EditAnywhere)
		UMainGameInstance* MainGameInstance;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		bool KeyStateOne;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		bool KeyStateTwo;
	UPROPERTY(Category = UserInterface, EditAnywhere, BlueprintReadWrite)
		bool KeyStateThree;

	UFUNCTION()
		void KeyCollected();
	
};
