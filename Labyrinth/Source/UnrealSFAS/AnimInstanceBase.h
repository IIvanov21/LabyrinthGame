// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

/**
 * 
 */
UENUM()
enum AnimationState
{
	Play = 0 UMETA(DisplayName="Play"),
	Pause = 1 UMETA(DisplayName = "Pause"),
	Resume = 2 UMETA(DisplayName = "Resume"),
	Stop = 3 UMETA(DisplayName = "Stop"),
};

UCLASS()
class UNREALSFAS_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
public:
	
	UAnimInstanceBase();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FAnimNotifyEvent AttackNotify;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UAnimMontage* PullMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UAnimMontage* PushMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsPushing;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsFalling;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsMovingRight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float AnimPlayRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsPushingRight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsJumping;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsCrouching;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsWalking;
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
		void UpdateAnimationProperties();
	UFUNCTION(BlueprintCallable, Category = "UpdateCrouch")
		void Crouched();
	UFUNCTION(BlueprintCallable, Category = "UpdateCrouch")
		void UnCrouched();
	UFUNCTION(BlueprintCallable, Category = "UpdateJump")
		void SetJumpTrue();
	UFUNCTION(BlueprintCallable, Category = "UpdateJump")
		void SetJumpFalse();
	UFUNCTION(BlueprintCallable, Category = "UpdatePush")
		void SetPush(bool condition);
	UFUNCTION(BlueprintCallable, Category = "UpdatePull")
		void SetPull(bool condition);
	UFUNCTION(BlueprintCallable, Category = "UpdateWalk")
		void SetWalk(bool condition);
	UFUNCTION(BlueprintCallable, Category = "UpdateWalk")
		void PlayAnimation(FName Animation, AnimationState State);
};
