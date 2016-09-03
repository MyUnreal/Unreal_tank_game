// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
	auto Name = GetName(); // Left or Right Track depending of the input used
	//UE_LOG(LogTemp, Warning, TEXT("%s: %f"), *Name, Throttle)

	//Clamp thottle value for the use not over drive the tank
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;  //GetForwardVector gives the direction of the track, Pivot axis...
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //This cast allows to us apply force to the Component, only the getowner->getrootcomponent won't
	//With The cast I can AddForceAtLocation 
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


