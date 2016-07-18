// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledPawn();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller - No Controlled Tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller - %s"), *(ControlledTank->GetName()));
	}
}

ATank* ATankPlayerController::GetControlledPawn() const {

	/*APawn* TankPawn = GetPawn();
	ATank* Tank = Cast<ATank>(TankPawn);
	ATank* Tank = Cast<ATank>(GetPawn());
	return Tank;*/

	return Cast<ATank>(GetPawn());
	

}




