// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndAnimationAnimNotify.generated.h"

/**
 * Simple notify for the end of an animation.
 * Can be used for precise animation control events.
 */
UCLASS()
class UNREALSFAS_API UEndAnimationAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
