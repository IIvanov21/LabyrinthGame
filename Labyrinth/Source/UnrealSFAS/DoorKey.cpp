// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorKey.h"
#include "Components/StaticMeshComponent.h"
#include "UnrealSFASCharacter.h"
#include "PlayerControllerBase.h"

// Sets default values
ADoorKey::ADoorKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key Mesh"));
	KeyMesh->SetSimulatePhysics(false);
	KeyMesh->SetupAttachment(RootComponent);
	SetRootComponent(KeyMesh);
}

// Called when the game starts or when spawned
void ADoorKey::BeginPlay()
{
	Super::BeginPlay();
	//OnActorHit.AddDynamic(this, &ADoorKey::OnHit);
	KeyMesh->OnComponentBeginOverlap.AddDynamic(this, &ADoorKey::OnOverlapBegin);
	KeyMesh->OnComponentEndOverlap.AddDynamic(this, &ADoorKey::OnOverlapEnd);
	PlayerController = Cast<APlayerControllerBase>(GetWorld()->GetFirstPlayerController());
	
}



// Called every frame
void ADoorKey::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator KeyRotator = FRotator(0.0f, 2.0f, 0.0f);
	KeyMesh->AddLocalRotation(KeyRotator);
}



void ADoorKey::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(AUnrealSFASCharacter::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Key Collected!"));
		PlayerController->SetKey();
		AUnrealSFASCharacter* Player = Cast<AUnrealSFASCharacter>(OtherActor);
		Player->SetDoorKeyState();
		Destroy();
	}
}


void ADoorKey::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass()->IsChildOf(AUnrealSFASCharacter::StaticClass()))
	{
		/*Place holder code for now!*/
	}
}
