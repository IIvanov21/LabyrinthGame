// Fill out your copyright notice in the Description page of Project Settings.


#include "PortalActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
APortalActor::APortalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(50.0f, 100.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	SetRootComponent(TriggerCapsule);
	TriggerCapsule->SetupAttachment(RootComponent);
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	ActorMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APortalActor::BeginPlay()
{
	Super::BeginPlay();
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &APortalActor::OnOverlapBegin);
}

// Called every frame
void APortalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortalActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		if (this->ActorHasTag("PuzzleOne"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Should teleport to Puzzle 1!"));
			UGameplayStatics::OpenLevel(GetWorld(), "PuzzleOne");

		}
		if (this->ActorHasTag("PuzzleTwo"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Should teleport to Puzzle 2!"));
			UGameplayStatics::OpenLevel(GetWorld(), "PuzzleTwo");

		}
		if (this->ActorHasTag("PuzzleThree"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Should teleport to Puzzle 3!"));
			UGameplayStatics::OpenLevel(GetWorld(), "PuzzleThree");

		}
		if (this->ActorHasTag("MainWorld"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Should teleport to Puzzle 4!"));
			UGameplayStatics::OpenLevel(GetWorld(), "MazeBase");

		}


	}
}

