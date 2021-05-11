// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*
	 * Setup the Mesh and it's properties.
	 */
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetSimulatePhysics(true);
	ProjectileMesh->SetEnableGravity(false);
	SetRootComponent(ProjectileMesh);

	/*
	 * Declare the projectile movement settings.
	 */
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovement->MaxSpeed = MovementSpeed;
	ProjectileMovement->InitialSpeed = MovementSpeed;
	InitialLifeSpan = 5.0f;
}

void AProjectileActor::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor->ActorHasTag("Enemy"))
	{
		/*
		 * Apply the damage to the given actor.
		 */
		UE_LOG(LogTemp, Warning, TEXT("Object hit!"));
		AActor* ProjectileOwner = GetOwner();
		if (ProjectileOwner == nullptr)return;
		UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, ProjectileOwner->GetInstigatorController(), this, UDamageType::StaticClass());
		Destroy();
	}
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	//Bind dynamics
	OnActorHit.AddDynamic(this, &AProjectileActor::OnHit);
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ProjectileMesh->AddRelativeRotation(FRotator(0.0f, 30.0f, 0.0f));
}

