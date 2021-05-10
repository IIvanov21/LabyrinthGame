// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialAnimNotify.h"
#include "AnimInstanceBase.h"
#include "UnrealSFASCharacter.h"
void USpecialAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// print method name to screen
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Purple, __FUNCTION__);
	UE_LOG(LogTemp, Warning, TEXT("Animation attacked played!"));
	AUnrealSFASCharacter* CharacterController = Cast<AUnrealSFASCharacter>(MeshComp->GetOwner());
	if (CharacterController != nullptr)CharacterController->CreateProjectile();
}
