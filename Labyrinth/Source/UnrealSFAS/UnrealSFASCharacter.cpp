// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealSFASCharacter.h"

#include "AnimInstanceBase.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PushActor.h"
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
	GetCharacterMovement()->JumpZVelocity = 600.f;
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
	
	PlayerInputComponent->BindAxis("MoveForward", this, &AUnrealSFASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUnrealSFASCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUnrealSFASCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUnrealSFASCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AUnrealSFASCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AUnrealSFASCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AUnrealSFASCharacter::OnResetVR);

	PlayerInputComponent->BindAction("ShowPlayerPos", IE_Pressed, this, &AUnrealSFASCharacter::ShowPlayerCoordinates);
}

void AUnrealSFASCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimationUpdate = Cast<UAnimInstanceBase>(GetMesh()->GetAnimInstance());


}

void AUnrealSFASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerMovement==Interaction)
	{
		
	}
}

void AUnrealSFASCharacter::Jump()
{
	Super::Jump();
	AnimationUpdate->SetJumpTrue();
}

void AUnrealSFASCharacter::StopJumping()
{
	Super::StopJumping();
}



void AUnrealSFASCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	AnimationUpdate->SetJumpFalse();
	
}



void AUnrealSFASCharacter::MoveInteractionPressed()
{
	if (Interacted)
	{
		AnimationUpdate->PlayAnimation("Pull", Resume);
		
		//InteractedActor->SetActorLocation(GetActorForwardVector()*5.0f );
	
	}
}

void AUnrealSFASCharacter::MoveInteractionReleased()
{
	if (Interacted)
	{
		AnimationUpdate->PlayAnimation("Pull", Pause);
	}
}

void AUnrealSFASCharacter::PlayPushPull(float Value)
{
	if (Interacted)
	{
		if(Value ==0)AnimationUpdate->PlayAnimation("Pull", Play);
		if (Value > 0.0f)
		{
			AnimationUpdate->SetPush(true);
			AnimationUpdate->SetWalk(false);
			AnimationUpdate->PlayAnimation("Pull", Stop);
		}
		else if (Value < 0.0f)
		{
			AnimationUpdate->SetPush(false);
			AnimationUpdate->SetWalk(false);
			AnimationUpdate->PlayAnimation("Pull", Play);

		}


	}
	else
	{
		AnimationUpdate->SetWalk(true);
		AnimationUpdate->SetPush(false);
	}
}

void AUnrealSFASCharacter::PushActorForwards(float Value)
{
	float CastRange = 50.0f;
	float DistanceToActor = GetDistanceTo(InteractedActor);
	if(DistanceToActor>1.0f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Distance is greater!"));
		FString ActorName = InteractedActor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Hit something: %s"), *ActorName);
		InteractedActor->AddActorWorldOffset(GetActorForwardVector()*5.0f);
	}
}

void AUnrealSFASCharacter::PushActorRight(float Value)
{
	float CastRange = 50.0f;
	float DistanceToActor = GetDistanceTo(InteractedActor);
	
}
void AUnrealSFASCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressing Interact."));
	
	float CastRange = 50.0f;
	FVector EndPoint = GetActorLocation() + GetActorRotation().Vector() * CastRange;
	FHitResult Hit;
	bool ObjectInRange = GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), EndPoint, ECC_Visibility);
	if(ObjectInRange)
	{
		if(Hit.GetActor()->ActorHasTag("Interact"))
		{
			UE_LOG(LogTemp, Warning, TEXT("You can interact with this actor."));
			Interacted = !Interacted;
			PlayPushPull(0);
			InteractedActor = Hit.GetActor();
			//GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
			GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f); // ...at this rotation rate
			InteractedActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			//InteractedActor->DisableComponentsSimulatePhysics();
			PlayerMovement = Interaction;

			//UE_LOG(LogTemp, Warning, TEXT("Actor Root attached!"));
		}
	}
	else
	{
		Interacted = false;
		AnimationUpdate->PlayAnimation("Pull", Stop);
		//GetCharacterMovement()->bOrientRotationToMovement = true; 	
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
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
			PlayPushPull(Value);

		}
	}
	else if(PlayerMovement== Interaction)
	{
		//PushActorForwards(Value);

		AddMovementInput(GetActorForwardVector() ,Value);

	}
	
		
	
	
}

void AUnrealSFASCharacter::MoveRight(float Value)
{
	if (PlayerMovement == Walking)
	{
		if ((Controller != NULL) && (Value != 0.0f) && !Interacted)
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
	else if(Interacted)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}
void AUnrealSFASCharacter::ShowPlayerCoordinates()
{
	//UE_LOG(LogTemp, Warning, TEXT("Player position: %d %f %s"),GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);

}
