// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Everything here in comments goes to the blueprint comments when hover
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories=("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSec);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20; //Sensible value

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40; 

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0; 

	
	
};
