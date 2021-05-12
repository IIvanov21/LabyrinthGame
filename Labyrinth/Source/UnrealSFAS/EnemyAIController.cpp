// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	AActor* Actor = GetPawn();
	
}



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

