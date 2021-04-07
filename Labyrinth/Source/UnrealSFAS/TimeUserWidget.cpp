// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeUserWidget.h"



void UTimeUserWidget::GetTimer(int timerIn)
{
	Minutes = timerIn / 60;
	timerIn = timerIn % 60;
	Seconds = timerIn;
	if(Seconds < 10)TimeDisplay = FString::FromInt(Minutes) + ":0" + FString::FromInt(Seconds);
	else TimeDisplay = FString::FromInt(Minutes) + ":" + FString::FromInt(Seconds);
}
