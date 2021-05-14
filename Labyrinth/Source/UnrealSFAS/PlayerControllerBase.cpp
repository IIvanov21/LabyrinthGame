// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUserWidget.h"
#include "TimeUserWidget.h"
#include "KeyUserWidget.h"
#include "HealthUserWidget.h"
#include "MainGameInstance.h"
APlayerControllerBase::APlayerControllerBase()
{
	
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	//Create all the UI elements for the level
	MinimapUI = CreateWidget(this, MinimapClass);
	if (MinimapUI != nullptr)MinimapUI->AddToViewport();

	UE_LOG(LogTemp, Warning, TEXT("Time: %a"), Time);
	
	ScoreUI = CreateWidget(this, ScoreClass);
	ScoreText = Cast<UScoreUserWidget>(ScoreUI);
	SetScore(0);

	TimeUI = CreateWidget(this, TimeClass);
	if (TimeUI != nullptr)TimeUI->AddToViewport();
	TimeText = Cast<UTimeUserWidget>(TimeUI);
	
	KeyUI = CreateWidget(this, KeyClass);
	if (KeyUI != nullptr)KeyUI->AddToViewport();
	KeySet = Cast<UKeyUserWidget>(KeyUI);
	
	CrosshairUI = CreateWidget(this, CrosshairClass);

	HealthbarUI = CreateWidget(this, HealthbarClass);
	if (HealthbarUI != nullptr)HealthbarUI->AddToViewport();
	HealthHandle = Cast<UHealthUserWidget>(HealthbarUI);

}





void APlayerControllerBase::DrawCrosshair(bool Draw)
{
	if (CrosshairUI != nullptr && Draw)CrosshairUI->AddToViewport();
	else if(CrosshairUI!=nullptr && !Draw)CrosshairUI->RemoveFromViewport();
}

void APlayerControllerBase::SetScore(int Points)
{
	
	ScoreText->UpdateScore(Points);
	
}

void APlayerControllerBase::SetTimer(int timeIn)
{
	
	TimeText->GetTimer(timeIn);
}

void APlayerControllerBase::SetKey()
{
	KeySet->KeyCollected();
}

void APlayerControllerBase::UpdateHealthStatus(int HealthIn)
{
	
	HealthHandle->SetHealth(HealthIn);
}
