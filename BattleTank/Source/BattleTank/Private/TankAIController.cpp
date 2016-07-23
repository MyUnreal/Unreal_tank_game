// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	/*auto ControlledAITank = GetControlledAIPawn();
	if (!ControlledAITank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller - No Controlled Tank by AI"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller - %s"), *(ControlledAITank->GetName()));
	}*/

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller - No Player Tank found"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Found Player Tank- %s"), *(PlayerTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledAITank() const {

	return Cast<ATank>(GetPawn());
}


ATank* ATankAIController::GetPlayerTank() const {

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}
  	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank()) {
		//Aims towards the player
		//Aim at the player
		GetControlledAITank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
}
