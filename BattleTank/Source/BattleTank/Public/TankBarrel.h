// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Everything here in comments goes to the blueprint comments when hover
 */
UCLASS(meta = (BlueprintSpawnableComponent))//, hidecategories=("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 is max downword speed and +1 is max upward speed 
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10; //Sensible value

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40; 

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0; 

	
	
};
