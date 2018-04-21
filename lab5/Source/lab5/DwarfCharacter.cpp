// Fill out your copyright notice in the Description page of Project Settings.

#include "lab5.h"
#include "DwarfCharacter.h"
#include "DwarfAIController.h"
#include "lab5Character.h"

// Sets default values
ADwarfCharacter::ADwarfCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = ADwarfAIController::StaticClass();
}

// Called when the game starts or when spawned
void ADwarfCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADwarfCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ADwarfCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

float ADwarfCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.0f) {
		Health -= ActualDamage;
		if (Health <= 0.0f) {
			// We're dead, don't allow further damage
			bCanBeDamaged = false;
			StopAttack();
			DwarfDies();
			if (GetController() != nullptr) {
				GetController()->UnPossess();
			}
		}
	}
	return ActualDamage;
}

void ADwarfCharacter::StartAttack() {
	PlayAnimMontage(AttackAnim);
	GetWorldTimerManager().SetTimer(AttackTimer, this, &ADwarfCharacter::HitPlayer, PlayAnimMontage(AttackAnim), true);
}

void ADwarfCharacter::StopAttack() {
	StopAnimMontage(AttackAnim);
	GetWorldTimerManager().ClearTimer(AttackTimer);
}

void ADwarfCharacter::KillDwarf() {
	Destroy();
}

void ADwarfCharacter::DwarfDies() {
	PlayAnimMontage(DeathAnim);
	GetWorldTimerManager().SetTimer(DeathTimer, this, &ADwarfCharacter::KillDwarf, PlayAnimMontage(DeathAnim) - 0.25f, false);
}

void ADwarfCharacter::HitPlayer() {
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	if (Pawn) {
		Pawn->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
	}
}