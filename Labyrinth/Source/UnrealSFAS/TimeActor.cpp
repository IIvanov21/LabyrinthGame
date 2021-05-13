// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeActor.h"
#include "PlayerControllerBase.h"
#include "MainGameInstance.h"
// Sets default values
ATimeActor::ATimeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//MainGameInstance = Cast<UMainGameInstance>(GetGameInstance());
}

// Called when the game starts or when spawned
void ATimeActor::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerControllerBase>(GetWorld()->GetFirstPlayerController());
	MainGameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (MainGameInstance != nullptr)TimeCountDown = MainGameInstance->Time;
}

// Called every frame
void ATimeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MainGameInstance->Time = TimeCountDown-GetWorld()->GetTimeSeconds();
	PlayerController->SetTimer(TimeCountDown - GetWorld()->GetTimeSeconds());
}

