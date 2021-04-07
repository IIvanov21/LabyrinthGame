// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeActor.h"
#include "PlayerControllerBase.h"
// Sets default values
ATimeActor::ATimeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeActor::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerControllerBase>(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void ATimeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerController->SetTimer(TimeCountDown - GetWorld()->GetTimeSeconds());
}

