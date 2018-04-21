// Fill out your copyright notice in the Description page of Project Settings.

#include "lab5.h"
#include "DwarfAIController.h"
#include "DwarfCharacter.h"

enum State {Start, Chase, Attack, Dead};

void ADwarfAIController::BeginPlay() {
	Super::BeginPlay();

	Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	currState = Start;
}

void ADwarfAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (currState == Start) {
		ChasePlayer();
	}
	else if (currState == Attack) {
		ADwarfCharacter* DwarfPawn = Cast<ADwarfCharacter>(GetPawn());
		if (DwarfPawn != nullptr) {
			FVector dwarfPos = DwarfPawn->GetActorLocation();
			if (FVector::Dist(dwarfPos, Pawn->GetActorLocation()) > Range) {
				if (DwarfPawn != nullptr) {
					DwarfPawn->StopAttack();
				}
				ChasePlayer();
			}
		}
	}
}

void ADwarfAIController::ChasePlayer() {
	MoveToActor(Pawn);
	currState = Chase;
}

void ADwarfAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) {
	if (Result == EPathFollowingResult::Success) {
		currState = Attack;
		ADwarfCharacter* DwarfPawn = Cast<ADwarfCharacter>(GetPawn());
		if (DwarfPawn != nullptr) {
			DwarfPawn->StartAttack();
		}
	}
}