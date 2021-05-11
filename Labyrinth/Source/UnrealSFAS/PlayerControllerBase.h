// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"


class UScoreUserWidget;
class UTimeUserWidget;
class UKeyUserWidget;
/**
 * 
 */
UCLASS()
class UNREALSFAS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void DrawCrosshair(bool Draw);
	void SetScore(int Points);
	void  SetTimer(int timeIn);
	void SetKey();
private:
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
		TSubclassOf<UUserWidget> ScoreClass;
	UPROPERTY(EditAnywhere)
		UUserWidget* ScoreUI;
	UPROPERTY(EditAnywhere)
		UScoreUserWidget* ScoreText;


	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> CrosshairClass;
	UPROPERTY(EditAnywhere)
		UUserWidget* CrosshairUI;
};
