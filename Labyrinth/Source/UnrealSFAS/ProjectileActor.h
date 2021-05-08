// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"
class UProjectileMovementComponent;
class UGameplayStatics;
UCLASS()
class UNREALSFAS_API AProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();
private:
	UPROPERTY(EditAnywhere)
		float DamageAmount = 10.0f;
	UPROPERTY(EditAnywhere)
		float MovementSpeed = 1000.0f;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* ProjectileMovement;
	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
