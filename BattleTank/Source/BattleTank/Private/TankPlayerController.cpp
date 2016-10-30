// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	/*auto ControlledTank = GetControlledPawn();
	if (!ControlledTank) {
		//UE_LOG(LogTemp, Warning, TEXT("Player Controller - No Controlled Tank"));
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Player Controller - %s"), *(ControlledTank->GetName()));
	}*/
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller - No Aiming Component"));
	}
	
}


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

/*void ATankPlayerController::FoundAimingComponent (UTankAimingComponent* AimCompRef){
	

}*/

ATank* ATankPlayerController::GetControlledTank() const {

	/*APawn* TankPawn = GetPawn();
	ATank* Tank = Cast<ATank>(TankPawn);
	ATank* Tank = Cast<ATank>(GetPawn());
	return Tank;*/

	return Cast<ATank>(GetPawn());

}

void ATankPlayerController::AimTowardsCrosshair() {
	//I've got no tank in controll
	if (!ensure(GetControlledTank())) { return; }

	//Get World location through Crosshair
	FVector HitLocation; //Out parameter -> It will be modified (We need to get the HitLocation...)
	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}
}


//Get OUT parameter, true if hit landscape or tank
//As we pass an & later the HitLocation will be modified here, as an OUT parameter - Unrela Engine does things like This in a getter method and we must follow...
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {

	//Find the Crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY); //This methos has two & which means out parameters that change the ViewportSizeX and ViewPortSizeY, which is weird that these values are changed in a Get, But it's unreal way of doing so we must live with it.
	//De-project the screen position of the crosshair to a world direction
	//Location in pixels
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY);
	//UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *ScreenLocation.ToString());
	FVector LookDirection;
	if (GetLookingDirection(ScreenLocation, LookDirection)) {
		//Linetrace along that look direction, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;
}

//Returns true if aiming at something and that something is in The visibility Worlfd. Changes the HitLocation to the actual obejct the tanks is aiming at
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	//If The line trace succeeds we set hit location and return true, otherwise return false
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera //Hit anything Visible in Camera
	)) {
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}

//The & is for the Out parameter - the one that will be changed
bool ATankPlayerController::GetLookingDirection(FVector2D ScreenLocation, FVector& LookDirection) const{
	
	FVector CameraWorldLocation; //For Discarding
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
}