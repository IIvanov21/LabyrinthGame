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
	/*
	 * Control animation play rate, speed and angle.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float AnimPlayRate;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float AimWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float AimWalkAngle;
	/*
	 * Notifications and montages used for exactly timed animations.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FAnimNotifyEvent AttackNotify;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UAnimMontage* PullMontage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UAnimMontage* PushMontage;
	/*
	 * Control variables for the animator.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsPushing;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsFalling;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsMovingRight;
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool IsAimWalking;
	UFUNCTION(BlueprintCallable, Category = "UpdateAnimationProperties")
		void UpdateAnimationProperties();
	/*
	 * Switches to control animations.
	 */
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
	/*
	 * Handler to play a given animation montage.
	 */
	UFUNCTION(BlueprintCallable, Category = "UpdateWalk")
		void PlayAnimation(FName Animation, AnimationState State);
};
