// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * Controller for the Enemy Animation.
 * Allows to control Enemy Animation States with reference in Notify anims.
 */
UCLASS()
class UNREALSFAS_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UEnemyAnimInstance();
	/*
	 * Simple attack callers.
	 */
	UFUNCTION()
		void SetAttack(bool condition) { IsAttacking = condition; }
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsAttacking;
};
