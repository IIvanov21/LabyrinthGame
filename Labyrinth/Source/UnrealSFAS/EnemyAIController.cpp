// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/TargetPoint.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAnimInstance.h"
/*
 * Setup the enemy character control variables and get access to
 * the Player character.
 */
void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	AIPawn = GetPawn();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (EnemyBehaviorTree != nullptr)
	{
		RunBehaviorTree(EnemyBehaviorTree);
		UE_LOG(LogTemp, Warning, TEXT("BT Loaded!"));
	}
	GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), AIPawn->GetActorLocation());
	EnemyHealth = SetEnemyHealth;
	

}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}


/*
 * If the enemy has been hurt by the player reduce it's health or
 * destroy the controller and pawn reference.
 */
void AEnemyAIController::ReduceEnemyHealth(int DamageAmount)
{
	EnemyHealth -= DamageAmount;
	if (EnemyHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enemy Dead!"));
		GetPawn()->Destroy();
		
	}
	else UE_LOG(LogTemp, Warning, TEXT("Enemy Hurt!"));

}

