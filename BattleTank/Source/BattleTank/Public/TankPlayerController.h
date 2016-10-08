// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

//Forward declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	    UFUNCTION(BlueprintCallable, Category = "Setup")
		ATank* GetControlledTank() const;

private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairLocationX = 0.5f; //We defined that the small dot is 50% middle screen
	UPROPERTY(EditDefaultsOnly)
	float CrossHairLocationY = 0.3333f; //We defined that the small dot is 1/3 top of screen

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000; //MAx distance to Hit - 10km (Is in cm so is 10 000 00) The last 2 00 is form cm

    
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime );

	
	//Starts the tank moving the barrel twards the Crosshair - dot on screen
	void AimTowardsCrosshair();

	//Get OUT parameter, true if hit landscape or tank
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const;
	bool GetLookingDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
};
