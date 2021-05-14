// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

/*
 * Using the navigation box in the level. Generate a random location for the Enemy AI to patrol to.
 * This service gets called when the enemy has reached it's last patrol point.
 */
EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr)return EBTNodeResult::Failed;

	AActor* AIActor = OwnerComp.GetAIOwner()->GetPawn();
	float RandomRadius = 2000.0f;
	FNavLocation RandomLocation;

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	NavSys->GetRandomReachablePointInRadius(AIActor->GetActorLocation(), RandomRadius, RandomLocation);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("RandomLocation"), RandomLocation);

	return EBTNodeResult::Succeeded;
}