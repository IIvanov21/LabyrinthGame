// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthUserWidget.h"

void UHealthUserWidget::SetHealth(float HealthAmount)
{
	/*
	 * Progress bar in UI work in the range of 0 to 1.
	 * Hence the division by 100.
	 */
	Health = HealthAmount/100;
}
