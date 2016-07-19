// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledAITank = GetControlledAIPawn();
	if (!ControlledAITank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller - No Controlled Tank by AI"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller - %s"), *(ControlledAITank->GetName()));
	}
}

ATank* ATankAIController::GetControlledAIPawn() const {

	return Cast<ATank>(GetPawn());
}

