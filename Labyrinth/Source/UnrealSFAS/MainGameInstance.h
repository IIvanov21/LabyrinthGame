// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSFAS_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMainGameInstance(const FObjectInitializer& ObjectInitializer);
	UPROPERTY(EditAnywhere)
		float Time;
	UPROPERTY(EditAnywhere)
		float Score;
	UPROPERTY(EditAnywhere)
		float Health;
	


};
