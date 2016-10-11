// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state (What the aiming type)
UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked
};

//Forward Declaration
class UTankBarrel; 
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation, float LaunchSpeed);

	//The Starting Point of our projectiles are in Barrel. 
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	//The Starting Point of our projectiles are in Barrel. 
	void SetTurretReference(UTankTurret* TurretToSet);

protected:
	//To enable the calling in blueprint -> must be protected
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;

private:
	//The Barrel inherits form UObject in Unreal - And it's where the projectiles start
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	
};
