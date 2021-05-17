// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnActor.h"

// Sets default values
ARespawnActor::ARespawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Capsule"));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARespawnActor::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARespawnActor::OnOverlapBegin);
}

// Called every frame
void ARespawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARespawnActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player has overlapped!"));
		if (this->ActorHasTag("LevelOne"))OtherActor->SetActorLocation(FVector(70.0f, 10.0f, 120.0f));
		if (this->ActorHasTag("LevelTwo"))OtherActor->SetActorLocation(FVector(0.0f, 0.0f, 100.0f));
		if (this->ActorHasTag("LevelThree"))OtherActor->SetActorLocation(FVector(50.0f, 80.0f, 120.0f));


	}
}
