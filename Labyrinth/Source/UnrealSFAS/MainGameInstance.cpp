// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"


UMainGameInstance::UMainGameInstance(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	
	Time = 1200.0f;
	Health = 100;
	KeyOne = false;
	KeyTwo = false;
	KeyThree = false;
	KeysCollected = false;
}

void UMainGameInstance::ResetStats()
{
	Time = 1200.0f;
	Health = 100;
	KeyOne = false;
	KeyTwo = false;
	KeyThree = false;
	KeysCollected = false;
}
