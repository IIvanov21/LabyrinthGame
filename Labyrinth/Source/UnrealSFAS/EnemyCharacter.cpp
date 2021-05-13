// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "EnemyAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UnrealSFASCharacter.h"
// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	EnemyAnim = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	GetMesh()->OnComponentHit.AddDynamic(this, &AEnemyCharacter::OnCompHit);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector EndPoint = GetActorLocation()+GetActorForwardVector() * 100.0f;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	bool PlayerInRange = GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), EndPoint,ECC_Visibility);
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetActorLocation(), EndPoint, ETraceTypeQuery::TraceTypeQuery2,
		false, ActorsToIgnore, EDrawDebugTrace::Type::ForDuration, Hit, true, FLinearColor::Red, FLinearColor::Green, 2);
	if (EnemyAnim != nullptr)
	{
		if (Hit.GetActor() != nullptr && Hit.GetActor()->ActorHasTag("Player"))
		{
			EnemyAnim->SetAttack(true);
			IsEnemyAttacking = true;
		}
		else 
		{
			EnemyAnim->SetAttack(false);
			IsEnemyAttacking = false;
		}
	}
	else UE_LOG(LogTemp, Warning, TEXT("Enemy Anim is nullptr"));
	if (AttackTimer >= 0.0f)AttackTimer -= DeltaTime;
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::OnCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
	if (OtherActor->ActorHasTag("Player") && AttackTimer <= 0.0f && IsEnemyAttacking)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Enemy Comp Hit"));
		PlayerCharacter = Cast<AUnrealSFASCharacter>(OtherActor);
		if(PlayerCharacter!=nullptr)PlayerCharacter->DamagePlayer(EnemyDamage);
		AttackTimer = 1.0f;
	}
}


