// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h" //Although forward declaration in .h here we must include because we are going to call the methods
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true; //TODO Should Tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;

	//Could be this.Barrel->Barrel, if BarrelToSet was Barrel
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

	if(haveAimingSolution)
	{ //Calculate the OutLaunchVelocity
		//This will give the Normal of the vector for the launch projectile
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%f: Aiming Solution"), Time);
	}
	//If no Solution Found - Do Nothing
	else {		
		UE_LOG(LogTemp, Warning, TEXT("%f: No Aiming Solution"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	//Work-out the difference between the barrel totation and aimdirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator %s"), *DeltaRotator.ToString());
	//Moce the barrel the right amount this frame
	//Given a max elevation speed and the frame time
	Barrel->Elevate(DeltaRotator.Pitch);

}