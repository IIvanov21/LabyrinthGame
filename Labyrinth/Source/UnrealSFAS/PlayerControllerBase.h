// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PlayerControllerBase.generated.h"

class UScoreUserWidget;
class UTimeUserWidget;
class UKeyUserWidget;
class UHealthUserWidget;
class UMainGameInstance;
/**
 * 
 */
UCLASS()
class UNREALSFAS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerControllerBase();
	virtual void BeginPlay() override;
	void DrawCrosshair(bool Draw);
	void SetScore(int Points);
	void SetTimer(int timeIn);
	void SetKey();
	void UpdateHealthStatus(int HealthIn);
	int GetTimer() { return Time; }
private:
	UPROPERTY(EditAnywhere)
		UMainGameInstance* MainGameInstance;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> MinimapClass;
	UPROPERTY(EditAnywhere)
		UUserWidget* MinimapUI;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> KeyClass;
	UPROPERTY(EditAnywhere)
		UUserWidget* KeyUI;
	UPROPERTY(EditAnywhere)
		UKeyUserWidget* KeySet;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> TimeClass;
	UPROPERTY(EditAnywhere)
		UUserWidget* TimeUI;
	UPROPERTY(EditAnywhere)
		UTimeUserWidget* TimeText;
	UPROPERTY(EditAnywhere)
		int Time;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> ScoreClass;
	UPROPERTY(EditAnywhere)
		UUserWidget* ScoreUI;
	UPROPERTY(EditAnywhere)
		UScoreUserWidget* ScoreText;
	UPROPERTY(EditAnywhere)
		int Score;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> CrosshairClass;
	UPROPERTY(EditAnywhere)
		UUserWidget* CrosshairUI;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> HealthbarClass;
	UPROPERTY(EditAnywhere)
		UUserWidget* HealthbarUI;
	UPROPERTY(EditAnywhere)
		UHealthUserWidget* HealthHandle;
	UPROPERTY(EditAnywhere)
		int Health;
};
