// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateAbstractDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement")); //This will be availabe in the BluePrint Classes, adding a new default object
	ProjectileMovement->bAutoActivate = false;  //This prevents the projectile to auto fire in the begining

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProjectile::LaunchProjectile(float Speed) {
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("Projectile at Speed %f"), Speed)
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate(); //We have deactivated bAutoActivate = false
}


