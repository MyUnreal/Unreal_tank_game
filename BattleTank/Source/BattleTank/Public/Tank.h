// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//Forward declaration
class UTankAimingComponent;
class UTankBarrel; 
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);
	
	//To Be Called in the Blueprint as a function - The BarrelToSet Came Form the BluePrint itself (See Blueprint)
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);
	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//This property will be visible in Unreal
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 4500;  //sensible starting value of 1000 m/s (Unreal is in cm)

	UPROPERTY(EditAnywhere, Category = Setup)
	//UClass* ProjectileBlueprint; //Alternative http://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/TSubclassOf/ - Using the alternative
	TSubclassOf<AProjectile> ProjectileBlueprint;

	//Local barrel reference to spawn projectile
	UTankBarrel* Barrel = nullptr;

	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
	
};
