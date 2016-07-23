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


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledPawn() const {

	/*APawn* TankPawn = GetPawn();
	ATank* Tank = Cast<ATank>(TankPawn);
	ATank* Tank = Cast<ATank>(GetPawn());
	return Tank;*/

	return Cast<ATank>(GetPawn());
	

}

void ATankPlayerController::AimTowardsCrosshair() {
	//I've got no tank in controll
	if (!GetControlledPawn()) { return; }

	//Get World location through Crosshair
	FVector HitLocation; //Out parameter -> It will be modified (We need to get the HitLocation...)
	if (GetSightRayHitLocation(HitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
		//If hits something (landscape or other tank)
	}
}

//Get OUT parameter, true if hit landscape or tank
//As we pass an & later the HitLocation will be modified here, as an OUT parameter - Unrela Engine does things like This in a getter method and we must follow...
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {

	//HitLocation = FVector(1.0); //Just for testing purposes

	//Find the Crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); //This methos has two & which means out parameters that change the ViewportSizeX and ViewPortSizeY, which is weird that these values are changed in a Get, But it's unreal way of doing so we must live with it.
	//De-project the screen position of the crosshair to a world direction

	//Location in pixels
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY);
	UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *ScreenLocation.ToString());
	//Linetrace along that look direction, and see what we hit (up to max range)


	return true;
}


