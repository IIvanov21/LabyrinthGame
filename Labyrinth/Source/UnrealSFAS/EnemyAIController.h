// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSFAS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	APawn* AIPawn;
	APawn* PlayerPawn;
	int EnemyHealth;

	
public:
	UPROPERTY(EditAnywhere)
		UBehaviorTree* EnemyBehaviorTree;
	UPROPERTY(EditAnywhere)
		int SetEnemyHealth;
	UPROPERTY(EditAnywhere)
		int EnemyDamage;
	UFUNCTION()
		void ReduceEnemyHealth(int DamageAmount);
};