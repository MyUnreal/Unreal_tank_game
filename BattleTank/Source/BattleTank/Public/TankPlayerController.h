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
	
public:
	ATank* GetControlledPawn() const;
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime );

private:
	//Starts the tank moving the barrel twards the Crosshair - dot on screen
	void AimTowardsCrosshair();

	//Get OUT parameter, true if hit landscape or tank
	bool GetSightRayHitLocation(FVector& HitLocation) const;
};
