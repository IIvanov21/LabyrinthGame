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
	
}

// Called every frame
void APushActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

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

