// Fill out your copyright notice in the Description page of Project Settings.

#include "lab5.h"
#include "SpawnManager.h"
#include "Engine/TargetPoint.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerHandle SpawnTimer;
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &ASpawnManager::OnSpawnTimer, SpawnTime, true);
}

// Called every frame
void ASpawnManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASpawnManager::OnSpawnTimer() {
	int num = SpawnPoints.Num();

	if (num == 0) {
		return;
	}

	int index = FMath::RandRange(0, num - 1);
	ATargetPoint* tpoint = SpawnPoints[index];
	FVector pos = SpawnPoints[index]->GetActorLocation();
	FRotator rot = SpawnPoints[index]->GetActorRotation();

	// Spawn an ACharacter of subclass CharacterClass, at specified position and rotation
	ACharacter* Char = GetWorld()->SpawnActor<ACharacter>(CharacterClass, pos, rot);
	if (Char) {
		// Spawn the AI controller for the character
		Char->SpawnDefaultController();
	}
}