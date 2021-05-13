// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
APlatformActor::APlatformActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	SetRootComponent(ActorMesh);
	SetCastRange = 200.0f;
	//ActorMesh->SetupAttachment(RootComponent);
}

void APlatformActor::CheckLocationLeft()
{
	float CastRange = SetCastRange;
	FVector EndPoint = GetActorLocation()+(GetActorRightVector()*CastRange);
	FHitResult Hit;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	bool ObjectInRange=UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation(), EndPoint, ETraceTypeQuery::TraceTypeQuery2,
		false, ActorsToIgnore,EDrawDebugTrace::Type::ForDuration, Hit, true, FLinearColor::Transparent, FLinearColor::Transparent, 2);
	if (ObjectInRange)
	{
		if (Hit.GetActor()->ActorHasTag("FinalPoint"))
		{
			FString ActorName = Hit.GetActor()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *ActorName);
			UE_LOG(LogTemp, Warning, TEXT("Arrived at location!"));
			MovementSpeed = -abs(MovementSpeed);
			MovingLeft = false;
		}
	}
}

void APlatformActor::CheckLocationRight()
{
	float CastRange = -SetCastRange;
	FVector EndPoint = GetActorLocation() + ((GetActorRightVector()) * CastRange);
	FHitResult Hit;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	bool ObjectInRange = UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation(), EndPoint, ETraceTypeQuery::TraceTypeQuery2,
		false, ActorsToIgnore, EDrawDebugTrace::Type::ForDuration, Hit, true, FLinearColor::Red, FLinearColor::Green, 2);
	if (ObjectInRange)
	{
		if (Hit.GetActor()->ActorHasTag("FinalPoint"))
		{
			FString ActorName = Hit.GetActor()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *ActorName);
			UE_LOG(LogTemp, Warning, TEXT("Arrived at location!"));
			MovementSpeed = abs(MovementSpeed);
			MovingLeft = true;
		}
	}
}

void APlatformActor::CheckLocationDown()
{
	float CastRange = -SetCastRange;
	FVector EndPoint = GetActorLocation() + ((GetActorUpVector()) * CastRange);
	FHitResult Hit;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	bool ObjectInRange = UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation(), EndPoint, ETraceTypeQuery::TraceTypeQuery2,
		false, ActorsToIgnore, EDrawDebugTrace::Type::ForDuration, Hit, true, FLinearColor::Red, FLinearColor::Green, 2);
	if (ObjectInRange)
	{
		if (Hit.GetActor()->ActorHasTag("FinalPoint"))
		{
			FString ActorName = Hit.GetActor()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *ActorName);
			UE_LOG(LogTemp, Warning, TEXT("Arrived at location!"));
			MovementSpeed = abs(MovementSpeed);
			MovingUp = true;
		}
	}
}

void APlatformActor::CheckLocationUp()
{
	float CastRange = SetCastRange;
	FVector EndPoint = GetActorLocation() + ((GetActorUpVector()) * CastRange);
	FHitResult Hit;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	bool ObjectInRange = UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation(), EndPoint, ETraceTypeQuery::TraceTypeQuery2,
		false, ActorsToIgnore, EDrawDebugTrace::Type::ForDuration, Hit, true, FLinearColor::Red, FLinearColor::Green, 2);
	if (ObjectInRange)
	{
		if (Hit.GetActor()->ActorHasTag("FinalPoint"))
		{
			FString ActorName = Hit.GetActor()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *ActorName);
			UE_LOG(LogTemp, Warning, TEXT("Arrived at location!"));
			MovementSpeed = -abs(MovementSpeed);
			MovingUp = false;
		}
	}
}
// Called when the game starts or when spawned
void APlatformActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (MoveSideways)
	{
		AddActorWorldOffset((GetActorRightVector() * MovementSpeed) * DeltaTime);
		if (MovingLeft)
		{
			CheckLocationLeft();
		}
		else
		{
			CheckLocationRight();
		}
	}
	else if(!MoveSideways)
	{
		AddActorWorldOffset((GetActorUpVector() * MovementSpeed) * DeltaTime);
		if (MovingUp)
		{
			CheckLocationUp();
		}
		else
		{
			CheckLocationDown();
		}
	}
}

