// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ChangeStateAnimNotify.generated.h"

/**
 * Anim notification to switch Player State at precise animation frame.
 */
UCLASS()
class UNREALSFAS_API UChangeStateAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
