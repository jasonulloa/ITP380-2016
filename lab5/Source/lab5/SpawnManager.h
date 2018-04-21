// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class LAB5_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void OnSpawnTimer();
protected:
	UPROPERTY(EditAnywhere)
	TArray<class ATargetPoint*> SpawnPoints;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACharacter> CharacterClass;

	UPROPERTY(EditAnywhere)
	float SpawnTime;
};
