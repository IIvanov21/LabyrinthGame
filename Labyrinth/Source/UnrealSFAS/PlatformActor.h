// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class UNREALSFAS_API APlatformActor : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformActor();
	//Ray Cast to finish point
	UFUNCTION()
		void CheckLocationLeft();
	UFUNCTION()
		void CheckLocationRight();
	UFUNCTION()
		void CheckLocationUp();
	UFUNCTION()
		void CheckLocationDown();
	/*
	 * Switches for direction of the platform.
	 */
	UPROPERTY(EditAnywhere)
		bool MovingLeft = true;
	UPROPERTY(EditAnywhere)
		bool MovingUp = true;
	UPROPERTY(EditAnywhere)
		bool MoveSideways=true;
	/*
	 * Control variables for platform speed and range.
	 */
	UPROPERTY(EditAnywhere)
	float MovementSpeed = 30.0f;
	UPROPERTY(EditAnywhere)
		float SetCastRange;
private:
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ActorMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
