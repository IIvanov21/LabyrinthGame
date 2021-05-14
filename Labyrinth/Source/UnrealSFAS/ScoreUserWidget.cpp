// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreUserWidget.h"

/*
 * Update the score display.
 */
void UScoreUserWidget::UpdateScore(int Points)
{
	CurrentScore += Points;
	Score = FString::FromInt(CurrentScore);

}
