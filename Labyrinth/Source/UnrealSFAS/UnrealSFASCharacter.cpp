// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSFASCharacter.h"

#include "AnimInstanceBase.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "PlayerControllerBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "MainGameInstance.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PushActor.h"
#include "ProjectileActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
//////////////////////////////////////////////////////////////////////////
// AUnrealSFASCharacter

AUnrealSFASCharacter::AUnrealSFASCharacter()
{
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	//Create a Minimap spring arm
	MiniMapSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Minimap Arm"));
	MiniMapSpringArm->SetupAttachment(RootComponent);
	MiniMapSpringArm->TargetArmLength = 300.0f;
	MiniMapSpringArm->bUsePawnControlRotation = false; // Prevent rotation of the arm based on the controller
	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	//Create Minimap camera
	MiniMapCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("Minimap Camera"));
	MiniMapCamera->SetupAttachment(MiniMapSpringArm);
	PlayerMovement = Walking;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(GetMesh());
	CameraDefault = CreateDefaultSubobject<UArrowComponent>(TEXT("CameraDefault"));
	CameraDefault->SetupAttachment(GetCapsuleComponent());
	// declare overlap events
	// declare trigger capsule
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(45.0f, 100.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

}

/*
 * Update the player state from other classes.
 */
void AUnrealSFASCharacter::ChangeState(PlayerMovementState State)
{
	PlayerMovement = State;
}

/*
 * Update Key and Door states.
 */
void AUnrealSFASCharacter::SetDoorKeyState()
{
	if(MainGameInstance->KeyOne && MainGameInstance->KeyTwo && MainGameInstance->KeyThree)
	{
		MainGameInstance->KeysCollected = true;
	}
}

bool AUnrealSFASCharacter::GetDoorKeyState()
{
	return MainGameInstance->KeysCollected;
}






//////////////////////////////////////////////////////////////////////////
// Input
void AUnrealSFASCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AUnrealSFASCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AUnrealSFASCharacter::StopJumping);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AUnrealSFASCharacter::Interact);
	PlayerInputComponent->BindAction("PressedMove", IE_Pressed, this, &AUnrealSFASCharacter::MoveInteractionPressed);
	PlayerInputComponent->BindAction("PressedMove", IE_Released,this, &AUnrealSFASCharacter::MoveInteractionReleased);


	/*Create the projectile itself*/
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AUnrealSFASCharacter::OnBeginFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AUnrealSFASCharacter::OnEndFire);
	/*Get into aim position bindings*/
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AUnrealSFASCharacter::OnAimBegin);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AUnrealSFASCharacter::OnAimEnd);

	/*Movement bindings*/
	PlayerInputComponent->BindAxis("MoveForward", this, &AUnrealSFASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUnrealSFASCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn", this, &AUnrealSFASCharacter::SetRotateAmount);

	PlayerInputComponent->BindAxis("TurnRate", this, &AUnrealSFASCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUnrealSFASCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AUnrealSFASCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AUnrealSFASCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AUnrealSFASCharacter::OnResetVR);

}

/*
 * Initiate attack animation.
 */
void AUnrealSFASCharacter::OnBeginFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire Pressed!"));
	if (PlayerMovement==Aim) AnimationUpdate->IsAttacking = true;
}

void AUnrealSFASCharacter::OnEndFire()
{
	UE_LOG(LogTemp, Warning, TEXT("Fire Released!"));
	
	
}
/*
 * Transition to Aim state
 * Allow it to only happen while in Walking State
 */
void AUnrealSFASCharacter::OnAimBegin()
{
	if (PlayerMovement == Walking)
	{
		//Default camera arm position: FVector(370.0f, 35.0f, 65.0f)
		/*
		 * Reset controller orientation and add a crosshair to the screen while aiming.
		 */
		GetController()->SetControlRotation(CameraDefault->GetComponentRotation());
		FollowCamera->SetRelativeLocation(FVector(370.0f, 35.0f, 65.0f));
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f);
		PlayerMovement = Aim;
		PlayerController->DrawCrosshair(true);
		AnimationUpdate->IsAimWalking = true;
	}

	

}
/*
 * Reset the player back to normal Walking state.
 */
void AUnrealSFASCharacter::OnAimEnd()
{
	if (PlayerMovement == Aim)
	{
		FollowCamera->ResetRelativeTransform();
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
		PlayerMovement = Walking;
		FollowCamera->bUsePawnControlRotation = true;
		CameraBoom->bUsePawnControlRotation = true;
		AnimationUpdate->IsAimWalking = false;

		PlayerController->DrawCrosshair(false);
	}
}
/*
 * Make the actor follow the controller rotation while Aiming.
 */
void AUnrealSFASCharacter::SetRotateAmount(float Value)
{
	if (PlayerMovement == Aim)
	{
		if (Value != 0.0f)
		{
			SetActorRotation(FRotator(0.0f,GetControlRotation().Yaw,0.0f));
		}
	}
}

void AUnrealSFASCharacter::BeginPlay()
{
	Super::BeginPlay();
	/*Setup character Mesh Hit events*/
	GetMesh()->SetNotifyRigidBodyCollision(true);
	AnimationUpdate = Cast<UAnimInstanceBase>(GetMesh()->GetAnimInstance());
	PlayerController = Cast<APlayerControllerBase>(GetWorld()->GetFirstPlayerController());

	/*
	 * Setup player properties from the BP.
	 */
	MainGameInstance = Cast<UMainGameInstance>(GetGameInstance());
	if (MainGameInstance != nullptr)
	{
		PlayerHealth = MainGameInstance->Health;
	}
	
	GetCharacterMovement()->JumpZVelocity = 480.0f;

}

void AUnrealSFASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	 * Update UI elements.
	 */
	PlayerController->UpdateHealthStatus(PlayerHealth);
	PlayerController->SetKey();
	/*
	 * Check if the player is too far from the Push Actor.
	 * If the player is too far update to normal walking state.
	 * This allows to deal with edge detection i.e. if the push actor has fallen from a wall or a platform.
	 */
	if (PlayerMovement == Interaction && InteractedActor != nullptr)
	{
		float DistanceToObject = UKismetMathLibrary::Vector_Distance(GetActorLocation(), InteractedActor->GetActorLocation());
		if (DistanceToObject > 150.0f)
		{
			UpdateInteraction();
		}
	}
	else if (PlayerMovement == Walking)
	{
		/*
		 * Simple jump timer to allow the full jump animation to play
		 * before transitioning to Fall animation.
		 */
		if (JumpAnimUpdate > 0.0f)JumpAnimUpdate -= DeltaTime;
		if (GetCharacterMovement()->IsFalling() && JumpAnimUpdate <= 0.0f)
		{
			AnimationUpdate->IsFalling = true;
		}
	}
	else if (PlayerMovement == Aim)
	{
		/*
		 * Create a raycast to get a vector location which the projectile that will be shot towards to.
		 */
		AController* ControllerRef = GetController();
		FVector CameraLocation;
		FRotator CameraRotation;
		ControllerRef->GetPlayerViewPoint(CameraLocation, CameraRotation);
		float CastRange = 10000.0f;
		FVector EndPoint = CameraLocation + CameraRotation.Vector() * CastRange;
		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), EndPoint, ECC_Visibility);
		/*
		 * Make the projectile fly towards where the player was aiming.
		 */
		ProjectileSpawnPoint->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(ProjectileSpawnPoint->GetComponentLocation(), Hit.TraceEnd));
		
	}

}
/*
 * Play the jump animation when it's initiated.
 */
void AUnrealSFASCharacter::Jump()
{
	if (PlayerMovement == Walking)
	{
		Super::Jump();
		JumpAnimUpdate = 0.5f;
		AnimationUpdate->SetJumpTrue();
	}
}
/*
 * Allow to play fall animation while in the air.
 */
void AUnrealSFASCharacter::StopJumping()
{
	if (PlayerMovement == Walking)
	{
		Super::StopJumping();
	}
}


/*
 * Update the jump animation when the player has landed.
 */
void AUnrealSFASCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	AnimationUpdate->SetJumpFalse();
	AnimationUpdate->IsFalling = false;
}




/*
 * Allow the push actor to be pushed in only one direction.
 */
void AUnrealSFASCharacter::MoveInteractionPressed()
{
	
}

void AUnrealSFASCharacter::MoveInteractionReleased()
{
	MovingRight = true;
	MovingForwards = true;
}
/*
 * Update the Push/Pull animations correctly
 */
void AUnrealSFASCharacter::PlayPushPullForwards(float Value)
{
	if (PlayerMovement==Interaction)
	{
		/*
		 * Pause the animations while the player is idle.
		 */
		if (Value == 0.0f)
		{
			AnimationUpdate->PlayAnimation("Pull", Pause);
			AnimationUpdate->PlayAnimation("Push", Pause);
		}
		/*
		 * Play Push animation
		 */
		else if (Value > 0.0f)
		{
			AnimationUpdate->SetWalk(false);
			AnimationUpdate->PlayAnimation("Push", Play);
			AnimationUpdate->PlayAnimation("Push", Resume);
			AnimationUpdate->PlayAnimation("Pull", Stop);

		}
		/*
		 * Play Pull animation
		 */
		else if (Value < 0.0f)
		{
			AnimationUpdate->SetWalk(false);
			AnimationUpdate->PlayAnimation("Pull", Play);
			AnimationUpdate->PlayAnimation("Push", Stop);
			AnimationUpdate->PlayAnimation("Pull", Resume);


		}


	}
	else
	{//Reset back to normal walking animation state.
		AnimationUpdate->SetWalk(true);
	}
}
void AUnrealSFASCharacter::PlayPushPullRight(float Value)
{
	if (PlayerMovement == Interaction)
	{
		/*
		 * Pause animations.
		 */
		if (Value == 0.0f)
		{
			AnimationUpdate->AnimPlayRate = 0.0f;

		}
		/*
		 * Play Push right animation
		 */
		else if (Value > 0.0f)
		{
			AnimationUpdate->SetWalk(false);
			AnimationUpdate->AnimPlayRate = 1.0f;
			AnimationUpdate->IsMovingRight = true;
			AnimationUpdate->IsPushingRight = true;
			AnimationUpdate->IsPushing = true;
		}
		/*
		 * Play push left animation.
		 */
		else if (Value < 0.0f)
		{
			AnimationUpdate->SetWalk(false);
			AnimationUpdate->AnimPlayRate = 1.0f;
			AnimationUpdate->IsMovingRight = false;
			AnimationUpdate->IsPushingRight = true;
			AnimationUpdate->IsPushing = true;

		}

	}
	else
	{//Reset back to normal walking animation state.
		AnimationUpdate->SetWalk(true);
	}
}

/*
 * Make the push actor follow the player movement correctly.
 */
void AUnrealSFASCharacter::PushActorForwards(float Value)
{
	FString ActorName = InteractedActor->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *ActorName);
	InteractedActor->AddActorWorldOffset(((GetActorForwardVector() *GetVelocity().Size()) * Value)* GetWorld()->DeltaTimeSeconds);
	if(Value!=0.0f)MovingRight = false;
	InteractedActor->AddMovementInput(GetActorForwardVector() * Value);
}

void AUnrealSFASCharacter::PushActorRight(float Value)
{
	FString ActorName = InteractedActor->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *ActorName);
	InteractedActor->AddActorWorldOffset(((GetActorRightVector() * GetVelocity().Size()) * Value)*GetWorld()->DeltaTimeSeconds);
	if(Value!=0.0f)MovingForwards = false;
}

/*
 * Reset player movement to default walk state.
 */
void AUnrealSFASCharacter::UpdateInteraction()
{
	PlayerMovement = Walking;
	AnimationUpdate->PlayAnimation("Pull", Stop);
	AnimationUpdate->PlayAnimation("Push", Stop);
	AnimationUpdate->IsPushingRight = false;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	if (InteractedActor != nullptr)InteractedActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

/*
 * Create a projectile when the player initates attack state.
 */
void AUnrealSFASCharacter::CreateProjectile()
{
	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileActor* TempProjectile = GetWorld()->SpawnActor<AProjectileActor>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
	else UE_LOG(LogTemp, Warning, TEXT("Failed to get projectile class."));
}

/*
 * Simple raycast to check if the player is close enough to an interact object.
 */
void AUnrealSFASCharacter::Interact()
{
	if (PlayerMovement != Aim)//Allow check if only in walk state
	{
		UE_LOG(LogTemp, Warning, TEXT("Pressing Interact."));

		float CastRange = 80.0f;
		FVector EndPoint = GetActorLocation() + GetActorRotation().Vector() * CastRange;
		FHitResult Hit;
		bool ObjectInRange = GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), EndPoint, ECC_Visibility);
		if (ObjectInRange && PlayerMovement == Walking)
		{
			if (Hit.GetActor()->ActorHasTag("Interact"))
			{
				/*
				 * Prepare movement system for interaction and attack the Push actor to the player.
				 */
				UE_LOG(LogTemp, Warning, TEXT("You can interact with this actor."));
				PlayPushPullRight(0);
				PlayPushPullForwards(0);
				InteractedActor = Cast<APawn>(Hit.GetActor());
				GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f);
				InteractedActor->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
				PlayerMovement = Interaction;
				SetActorRotation(Cast<APushActor>(InteractedActor)->GetOrientation(GetActorLocation()));
				UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition(EOrientPositionSelector::Orientation);
				SetActorRelativeLocation(Cast<APushActor>(InteractedActor)->GetLocation(GetActorLocation()));
				AnimationUpdate->PlayAnimation("Pull", Play);
			}
		}
		else
		{
			/*
			 * Reset player movement back to default moving system.
			 */
			UpdateInteraction();


		}
	}
}



void AUnrealSFASCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}



void AUnrealSFASCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AUnrealSFASCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();

}

void AUnrealSFASCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUnrealSFASCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUnrealSFASCharacter::MoveForward(float Value)
{
	/*
	 * Default movement allows the player movement
	 * to follow the camera orientation.
	 */
	if (PlayerMovement == Walking)
	{

		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
			

		}
	
	}
	/*
	 * If the player has interacted with an object.
	 * The movement system will ignore the camera and allow the player to move only
	 * forwards and sideways.
	 */
	else if(PlayerMovement == Interaction && MovingForwards )
	{
		
		PushActorForwards(Value);
		if(AnimationUpdate->IsPushing)AddMovementInput(GetActorForwardVector()*Value ,0.1f);
		PlayPushPullForwards(Value);
	

	}
	/*
	 * While the player is Aim the movement starts to include strafing with A and D keys.
	 */
	else if (PlayerMovement == Aim)
	{

		AddMovementInput(GetActorForwardVector() * Value, 0.3f);
		AnimationUpdate->AimWalkSpeed = Value;



	}
	
		
	
	
}

void AUnrealSFASCharacter::MoveRight(float Value)
{
	
	/*
	 * Default movement allows the player movement
	 * to follow the camera orientation. 
	 */
	if (PlayerMovement == Walking)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		
		}
		
	}
	/*
	 * If the player has interacted with an object.
	 * The movement system will ignore the camera and allow the player to move only
	 * forwards and sideways.
	 */
	else if(PlayerMovement == Interaction && MovingRight)
	{
		
		PushActorRight(Value);
		if (AnimationUpdate->IsPushing)AddMovementInput(GetActorRightVector()*Value, 0.1f);
		PlayPushPullRight(Value);
		
	}
	/*
	 * While the player is Aim the movement starts to include strafing with A and D keys.
	 */
	else if (PlayerMovement == Aim)
	{

		AddMovementInput(GetActorRightVector() * Value, 0.3f);
		AnimationUpdate->AimWalkAngle = Value;

	}
}

/*
 * Handle player health system functions.
 */
void AUnrealSFASCharacter::DamagePlayer(int DamageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("Player is Hit!"));

	PlayerHealth -= DamageAmount;
	MainGameInstance->Health -= DamageAmount;
	PlayerController->UpdateHealthStatus(MainGameInstance->Health);
	/*
	 * Open Game over level if the player dies.
	 */
	if(PlayerHealth<=0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player has died!"));
		MainGameInstance->ResetStats();
		UGameplayStatics::OpenLevel(GetWorld(), "GameOverMenu");
	}
}
