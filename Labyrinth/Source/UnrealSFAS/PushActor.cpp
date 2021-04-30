// Fill out your copyright notice in the Description page of Project Settings.


#include "PushActor.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
APushActor::APushActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	ActorMesh->SetupAttachment(RootComponent);
	
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

