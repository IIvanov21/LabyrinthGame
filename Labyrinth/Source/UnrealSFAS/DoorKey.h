// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorKey.generated.h"
class ADoorActor;
class APlayerControllerBase;
class UMainGameInstance;
UCLASS()
class UNREALSFAS_API ADoorKey : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorKey();
private:
	UPROPERTY()
		UMainGameInstance* MainGameInstance;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* KeyMesh;
	UPROPERTY(EditAnywhere)
		APlayerControllerBase* PlayerController;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
							int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
