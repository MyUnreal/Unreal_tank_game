// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h" //Although forward declaration in .h here we must include because we are going to call the methods
#include "TankTurret.h" //Although forward declaration in .h here we must include because we are going to call the methods
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true; 

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet) {

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool haveAimingSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false, //There is a bug in this method all these parameters should be called in this way or it doesn't work...
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	auto Time = GetWorld()->GetTimeSeconds();

	if (haveAimingSolution)
	{ //Calculate the OutLaunchVelocity
		//This will give the Normal of the vector for the launch projectile
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%f: Aiming Solution"), Time);
	}
	//If no Solution Found - Do Nothing
}
	

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	if (!Barrel || !Turret) { return; }

	//Work-out the difference between the barrel totation and aimdirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator %s"), *DeltaRotator.ToString());
	//Moce the barrel the right amount this frame
	//Given a max elevation speed and the frame time
	Barrel->Elevate(DeltaRotator.Pitch);
	//Turret->Rotate(DeltaRotator.Yaw);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else // Avoid going the long-way round
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}

}
