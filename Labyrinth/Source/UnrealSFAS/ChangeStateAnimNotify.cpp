// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeStateAnimNotify.h"
#include "UnrealSFASCharacter.h"
void UChangeStateAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	TArray<FAnimNotifyTrack> Tracks = Animation->AnimNotifyTracks;
	AUnrealSFASCharacter* Character = Cast<AUnrealSFASCharacter>(MeshComp->GetOwner());
	for (auto track : Tracks)
	{
		if (track.TrackName == "Idle")
		{
			Character->ChangeState(Idle);
		}
		else
		{
			Character->ChangeState(Walking);
		}
	}
}
