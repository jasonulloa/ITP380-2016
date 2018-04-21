// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "DwarfAIController.generated.h"

/**
 * 
 */
UCLASS()
class LAB5_API ADwarfAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;
protected:
	UPROPERTY(EditAnywhere)
	float Range = 150.0f;
private:
	void ChasePlayer();

	class APawn* Pawn;
	int currState;
};
