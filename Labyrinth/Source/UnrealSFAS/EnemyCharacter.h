// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UEnemyAnimInstance;
class AUnrealSFASCharacter;
UCLASS()
class UNREALSFAS_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Enemy Animation Controller
	UPROPERTY(VisibleAnywhere)
		UEnemyAnimInstance* EnemyAnim;
	//Player access
	UPROPERTY(VisibleAnywhere)
		APawn* PlayerPawn;
	UPROPERTY(VisibleAnywhere)
		FHitResult Hit;
	// declare on hit
	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult);
	UPROPERTY()
		float AttackTimer = 0.0f;
	UPROPERTY(EditAnywhere)
		int EnemyDamage;
	UPROPERTY()
		AUnrealSFASCharacter* PlayerCharacter;
	UPROPERTY()
		bool IsEnemyAttacking = false;
};
