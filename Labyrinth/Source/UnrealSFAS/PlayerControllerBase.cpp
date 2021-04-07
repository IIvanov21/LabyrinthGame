// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUserWidget.h"
#include "TimeUserWidget.h"

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	//Create all the UI elements for the level
	MinimapUI = CreateWidget(this, MinimapClass);
	if (MinimapUI != nullptr)MinimapUI->AddToViewport();

	
	ScoreUI = CreateWidget(this, ScoreClass);
	if (ScoreUI != nullptr)ScoreUI->AddToViewport();

	TimeUI = CreateWidget(this, TimeClass);
	if (TimeUI != nullptr)TimeUI->AddToViewport();
	TimeText = Cast<UTimeUserWidget>(TimeUI);

	ScoreText = Cast<UScoreUserWidget>(ScoreUI);
	SetScore(0);

}





void APlayerControllerBase::SetScore(int Points)
{
	ScoreText->UpdateScore(Points);
}

void APlayerControllerBase::SetTimer(int timeIn)
{
	TimeText->GetTimer(timeIn);
}
