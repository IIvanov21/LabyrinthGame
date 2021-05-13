// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSFAS_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UEnemyAnimInstance();
	UFUNCTION()
		void SetAttack(bool condition) { IsAttacking = condition; }
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsAttacking;
};
