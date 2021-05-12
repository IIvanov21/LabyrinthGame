// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsAtLocation.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_IsAtLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AActor* EnemyAIController = OwnerComp.GetAIOwner();
	AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector PlayerLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector("PlayerPosition");
	float DistanceToPlayer = UKismetMathLibrary::Vector_Distance(EnemyAIController->GetActorLocation(),PlayerLocation);
	if(DistanceToPlayer<350.0f)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}
