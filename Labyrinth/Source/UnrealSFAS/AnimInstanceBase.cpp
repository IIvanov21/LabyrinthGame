// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceBase.h"

UAnimInstanceBase::UAnimInstanceBase()
{
	IsPulling = false;
	IsPushing = false;
	IsCrouching = false;
	IsJumping = false;
	IsWalking = false;
}



void UAnimInstanceBase::UpdateAnimationProperties()
{

}

void UAnimInstanceBase::Crouched()
{
	IsCrouching = true;
}

void UAnimInstanceBase::UnCrouched()
{
	IsCrouching = false;
}

void UAnimInstanceBase::SetJumpTrue()
{
	IsJumping = true;
	UE_LOG(LogTemp, Warning, TEXT("Jump set to true!"));
}

void UAnimInstanceBase::SetJumpFalse()
{
	IsJumping = false;
	UE_LOG(LogTemp, Warning, TEXT("Jump set to false!"));

}

void UAnimInstanceBase::SetPull(bool condition)
{
	IsPulling = condition;
}



void UAnimInstanceBase::SetPush(bool condition)
{
	IsPushing = condition;
}

void UAnimInstanceBase::SetWalk(bool condition)
{
	IsWalking = condition;
}

void UAnimInstanceBase::PlayAnimation(FName Animation, AnimationState State)
{
	
	if(State==AnimationState::Play)
	{
		if (PullMontage != nullptr && Animation == "Pull" )
		{
			
			UE_LOG(LogTemp, Warning, TEXT("Playing Pull Anim!"));
			if(!Montage_IsActive(PullMontage))Montage_Play(PullMontage);
		}
		else if (Animation == "Push")Montage_Play(PushMontage);
	}
	else if (State == AnimationState::Pause)
	{
		if (PullMontage!=nullptr && Animation == "Pull" && Montage_GetCurrentSection(PullMontage)== "Loop")Montage_Pause(PullMontage);
		else if (Animation == "Push")Montage_Pause(PushMontage);
		
	}
	else if (State == AnimationState::Resume)
	{
		if (PullMontage != nullptr && Animation == "Pull" && Montage_GetCurrentSection(PullMontage) == "Loop")Montage_Resume( PullMontage);
		else if (Animation == "Push")Montage_Resume(PushMontage);
	}
	else if (State == AnimationState::Stop)
	{
		if (PullMontage != nullptr && Animation == "Pull")Montage_Stop(0.25f,PullMontage);
		else if (Animation == "Push")Montage_Stop(0.25,PushMontage);
	}
}
