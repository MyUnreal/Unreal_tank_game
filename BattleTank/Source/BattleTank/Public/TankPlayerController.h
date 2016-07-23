// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere)
	float CrossHairLocationX = 0.5f; //We defined that the small dot is 50% middle screen
	UPROPERTY(EditAnywhere)
	float CrossHairLocationY = 0.333333f; //We defined that the small dot is 1/3 top of screen


	ATank* GetControlledPawn() const;
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime );

	
	//Starts the tank moving the barrel twards the Crosshair - dot on screen
	void AimTowardsCrosshair();

	//Get OUT parameter, true if hit landscape or tank
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookingDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
};
