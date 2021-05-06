// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PushActor.generated.h"
class UStaticMeshComponent;
UCLASS()
class UNREALSFAS_API APushActor : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APushActor();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ActorMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		FRotator GetOrientation(FVector ActorLocation);
	UFUNCTION()
		FVector GetLocation(FVector ActorLocation);

};
