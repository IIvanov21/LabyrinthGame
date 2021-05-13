// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyUserWidget.h"
#include "MainGameInstance.h"
void UKeyUserWidget::KeyCollected()
{
	MainGameInstance = Cast<UMainGameInstance>(GetGameInstance());
	
	KeyStateOne = MainGameInstance->KeyOne;
	KeyStateTwo = MainGameInstance->KeyTwo;
	KeyStateThree = MainGameInstance->KeyThree;
}
