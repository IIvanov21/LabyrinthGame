// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_IsInFront.generated.h"

/**
 * Service to check if the player is in front.
 */
UCLASS()
class UNREALSFAS_API UBTService_IsInFront : public UBTService_BlackboardBase
{
	GENERATED_BODY()
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	bool InFront(AActor* PlayerPawnIn, AActor* AIPawn);
};
