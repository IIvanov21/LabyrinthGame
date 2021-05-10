// Fill out your copyright notice in the Description page of Project Settings.


#include "EndAnimationAnimNotify.h"
#include "AnimInstanceBase.h"
void UEndAnimationAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UAnimInstanceBase* AnimationController = Cast<UAnimInstanceBase>(MeshComp->GetAnimInstance());
	if(AnimationController!=nullptr)AnimationController->IsAttacking = false;
}

