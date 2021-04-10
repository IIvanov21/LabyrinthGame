// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"

class USkeletalMeshComponent;
UCLASS()
class UNREALSFAS_API ADoorActor : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
		bool IsKeyCollected;
public:	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		USkeletalMeshComponent* DoorMesh;
	// Sets default values for this actor's properties
	ADoorActor();
	void KeyCollected();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
