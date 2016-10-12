// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declaration
class UTankAimingComponent;
class UTankBarrel; 
//class UTankTurret;
class AProjectile;
class UTankMovementComponent;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	//To Be callable in blueprints in this case in the TankPlayerController_BP
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	//This property will be visible in Unreal
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;  //sensible starting value of 1000 m/s (Unreal is in cm)

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	//UClass* ProjectileBlueprint; //Alternative http://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/ - Using the alternative
	TSubclassOf<AProjectile> ProjectileBlueprint;

	//Local barrel reference to spawn projectile
	UTankBarrel* Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
	
};
