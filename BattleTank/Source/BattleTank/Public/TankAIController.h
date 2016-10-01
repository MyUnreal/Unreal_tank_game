// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

//Forward declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	//How close the AI can get near the Player Tank
	float AcceptRadius = 3000; //3000 cm?
	
	
};
