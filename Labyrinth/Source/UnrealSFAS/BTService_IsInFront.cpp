// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsInFront.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
void UBTService_IsInFront::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AActor* Enemy = OwnerComp.GetAIOwner();
	AActor* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (InFront(PlayerPawn, Enemy))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
		OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("NoSight"));

	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("NoSight"), true);
	}
}

bool UBTService_IsInFront::InFront(AActor* PlayerPawnIn, AActor* AIPawn)
{
	FVector AIForwardVector = AIPawn->GetActorForwardVector();//Normalised
	FVector PlayerPositionVector = PlayerPawnIn->GetActorLocation();
	FVector AIPositionVector = AIPawn->GetActorLocation();
	FVector AIToPlayerVector = PlayerPositionVector - AIPositionVector;
	AIToPlayerVector.Normalize();
	float DirectionDotProduct = FVector::DotProduct(AIToPlayerVector, AIForwardVector);

	if (DirectionDotProduct > 0) return true;
	else return false;
}