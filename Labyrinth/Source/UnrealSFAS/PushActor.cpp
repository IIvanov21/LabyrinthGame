// Fill out your copyright notice in the Description page of Project Settings.


#include "PushActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
APushActor::APushActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	//ActorMesh->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void APushActor::BeginPlay()
{
	Super::BeginPlay();
	ActorMesh->OnComponentHit.AddDynamic(this, &APushActor::OnCompHit);
}

// Called every frame
void APushActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
/*
 * Get's all the sockets attached to the actor mesh and checks which
 * is the closest to the Player.
 * This helps to get correct orientation and position for the actor when
 * it get's attached to the player.
 */
/*
 * Gets Rotation
 */
FRotator APushActor::GetOrientation(FVector ActorLocation)
{
	
	TArray<FName>SocketNames = ActorMesh->GetAllSocketNames();
	TArray<FTransform> Sockets;
	for(auto name : SocketNames)
	{
		Sockets.Add( ActorMesh->GetSocketTransform(name));
	}
	Sockets.Sort([ActorLocation](const FTransform& A, const FTransform& B)
	{
		float DistanceA = UKismetMathLibrary::Vector_Distance(A.GetLocation(), ActorLocation);
		float DistanceB = UKismetMathLibrary::Vector_Distance(B.GetLocation(), ActorLocation);
		return DistanceA < DistanceB;
	});
	

	return Sockets[0].Rotator();
}
/*
 * Get's location.
 */
FVector APushActor::GetLocation(FVector ActorLocation)
{
	TArray<FName>SocketNames = ActorMesh->GetAllSocketNames();
	TArray<FTransform> Sockets;
	for (auto name : SocketNames)
	{
		Sockets.Add(ActorMesh->GetSocketTransform(name));
	}
	Sockets.Sort([ActorLocation](const FTransform& A, const FTransform& B)
	{
		float DistanceA = UKismetMathLibrary::Vector_Distance(A.GetLocation(), ActorLocation);
		float DistanceB = UKismetMathLibrary::Vector_Distance(B.GetLocation(), ActorLocation);
		return DistanceA < DistanceB;
	});


	return Sockets[0].GetLocation();
}

void APushActor::OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
	if(OtherActor->ActorHasTag("Projectile"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Interact hit!"));
		if(this->ActorHasTag("LevelOne"))
		{
			ActorMesh->SetVisibility(true);
			ActorMesh->SetMobility(EComponentMobility::Movable);
			AddActorWorldOffset(FVector(0.0f,50.0f,0.0f));
			ActorMesh->SetSimulatePhysics(true);
		}
		if (this->ActorHasTag("LevelTwo"))
		{
			ActorMesh->SetVisibility(true);
			ActorMesh->SetMobility(EComponentMobility::Movable);
			AddActorWorldOffset(FVector(-50.0f, 0.0f, 0.0f));
			ActorMesh->SetSimulatePhysics(true);
		}
	}
}
