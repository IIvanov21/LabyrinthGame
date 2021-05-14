// Fill out your copyright notice in the Description page of Project Settings.


#include "EndAnimationAnimNotify.h"
#include "AnimInstanceBase.h"
/*
 * Notification used to detect if the player Attack animation
 * has finished and update the Player animation state.
 */
void UEndAnimationAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UAnimInstanceBase* AnimationController = Cast<UAnimInstanceBase>(MeshComp->GetAnimInstance());
	if(AnimationController!=nullptr)AnimationController->IsAttacking = false;
}

