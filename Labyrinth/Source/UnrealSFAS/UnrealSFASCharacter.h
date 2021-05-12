// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Components/SceneCaptureComponent2D.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "UnrealSFASCharacter.generated.h"
class UAnimInstanceBase;
class AProjectileActor;
class APlayerControllerBase;
UENUM()
enum PlayerMovementState
{
	Idle UMETA(DisplayName = "Idle"),
	Walking UMETA(DisplayName = "Walking"),
	Interaction UMETA(DisplayName = "Interact"),
	Aim UMETA(DisplayName = "Aim"),

};

UCLASS(config=Game)
class AUnrealSFASCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* MiniMapSpringArm;
	
	UPROPERTY(EditAnywhere)
		USceneCaptureComponent2D* MiniMapCamera;
	UPROPERTY(EditAnywhere)
		bool IsKeyCollected;
	UPROPERTY(EditAnywhere)
		UAnimInstanceBase* AnimationUpdate;
	UPROPERTY(EditAnywhere)
		bool MovingForwards = true;
	UPROPERTY(EditAnywhere)
		bool MovingRight = true;
	UPROPERTY(EditAnywhere)
		bool IsPlayed = false;
	UPROPERTY(EditAnywhere)
		UArrowComponent* CameraDefault;
	
public:
	
	AUnrealSFASCharacter();
	UFUNCTION()
		void ChangeState(PlayerMovementState State);
	UFUNCTION()
		 void SetDoorKeyState() { IsKeyCollected = true; }
	UFUNCTION()
		 bool GetDoorKeyState() { return IsKeyCollected; }
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UFUNCTION()
		void Interact();

	UFUNCTION()
		void MoveInteractionPressed();
	UFUNCTION()
		void MoveInteractionReleased();
	UFUNCTION()
		void PlayPushPullForwards(float Value);
	UFUNCTION()
		void PlayPushPullRight(float Value);
	UFUNCTION()
		void PushActorForwards(float Value);
	UFUNCTION()
		void PushActorRight(float Value);
	UFUNCTION()
		void UpdateInteraction();
	UPROPERTY()
		APawn* InteractedActor;

	/*
	 * Providing access to projectile creation from other classes.
	 */
	UFUNCTION()
		void CreateProjectile();
private:
	PlayerMovementState PlayerMovement;

	/*Projectile throwable instance controller*/
	UPROPERTY(EditAnywhere)
		USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectileActor> ProjectileClass;
	/*
	 * Methods to create the projectile.
	 */
	void OnBeginFire();
	void OnEndFire();
	/*
	 * Aim functions
	 */
	FVector RelativeRotation;

	void OnAimBegin();
	void OnAimEnd();
	void SetRotateAmount(float Value);
	UPROPERTY()
		FVector DeltaLocation;
	UPROPERTY()
		FQuat   DeltaRotation;
	UPROPERTY(EditAnywhere)
		float RotateSpeed = 350.0f;
	UPROPERTY()
		APlayerControllerBase* PlayerController;
	
	/*
	 * Timers used to reset.
	 */
	float JumpAnimUpdate=0.0f;

protected:

	//// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


	/*Show Player coordinates*/
	void ShowPlayerCoordinates();

	void OnHit(AActor* HitComponent, AActor* OtherActor,  FVector NormalImpulse, const FHitResult& Hit);

	// Overlap
	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Jump() override;
	virtual void StopJumping() override;
	virtual void Landed(const FHitResult& Hit) override;
};

