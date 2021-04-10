// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"
#include "UnrealSFASCharacter.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsKeyCollected = false;
	DoorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Door Mesh"));
	SetRootComponent(DoorMesh);
	DoorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	DoorMesh->OnComponentHit.AddDynamic(this, &ADoorActor::OnCompHit);
	
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ADoorActor::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetClass()->IsChildOf(AUnrealSFASCharacter::StaticClass()))
	{
		AUnrealSFASCharacter* Player = Cast<AUnrealSFASCharacter>(OtherActor);
		IsKeyCollected = Player->GetDoorKeyState();
		if (IsKeyCollected)
		{
			UE_LOG(LogTemp, Warning, TEXT("Door Opened!"));
			DoorMesh->Play(false);
		}
		else UE_LOG(LogTemp, Warning, TEXT("Key needed"));
	}
}

void ADoorActor::KeyCollected()
{
	IsKeyCollected = !IsKeyCollected;
}
