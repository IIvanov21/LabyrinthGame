// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"
#include "UnrealSFASCharacter.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	IsKeyCollected = false;
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	SetRootComponent(DoorMesh);
	DoorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	DoorMesh->OnComponentBeginOverlap.AddDynamic(this, &ADoorActor::OnOverlapBegin);
	DoorMesh->OnComponentEndOverlap.AddDynamic(this, &ADoorActor::OnOverlapEnd);
}

// Called every frame
void ADoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoorActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(AUnrealSFASCharacter::StaticClass()) )
	{
		AUnrealSFASCharacter* Player = Cast<AUnrealSFASCharacter>(OtherActor);
		IsKeyCollected=Player->GetDoorKeyState();
		if (IsKeyCollected)
		{
			UE_LOG(LogTemp, Warning, TEXT("Door Opened!"));
			Destroy();
		}
		else UE_LOG(LogTemp, Warning, TEXT("Key needed"));
	}
}


void ADoorActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass()->IsChildOf(AUnrealSFASCharacter::StaticClass()))
	{
		/*Place holder code for now!*/
	}
}

void ADoorActor::KeyCollected()
{
	IsKeyCollected = !IsKeyCollected;
}
