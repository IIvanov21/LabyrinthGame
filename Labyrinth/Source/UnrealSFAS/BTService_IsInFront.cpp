// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsInFront.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"
/*
 * Calculate a dot product to check if the player is in front of the enemy.
 * If true Update enemy behaviour in the behaviour tree.
 */
void UBTService_IsInFront::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AActor* Enemy = OwnerComp.GetAIOwner();
	AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	bool IsInFront = InFront(PlayerPawn, Enemy);
	if (IsInFront && PlayerPawn != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("NoSight"));

	}
	else if (!IsInFront)
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("NoSight"), true);
	}
}
/*
 * Calculate the dot product.
 */
bool UBTService_IsInFront::InFront(AActor* PlayerPawnIn, AActor* AIPawn)
{
	
	float DotProduct = UKismetMathLibrary::Dot_VectorVector(AIPawn->GetActorLocation(), PlayerPawnIn->GetActorLocation());
	if (DotProduct >= 0) return true;
	return false;
}