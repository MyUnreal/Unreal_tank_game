// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"

#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet) {
	
	if (!LeftTrackToSet || !RightTrackToSet)
		return;
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	//UE_LOG(LogTemp, Warning, TEXT("%s: %f"), *Name, Throttle);
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward %f"), Throw)

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	//TODO: prevent double-speed due to dual controls
}

void UTankMovementComponent::IntendMoveRight(float Throw) {
	//UE_LOG(LogTemp, Warning, TEXT("%s: %f"), *Name, Throttle);
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward %f"), Throw)
	if (!LeftTrack || !RightTrack)
		return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	//TODO: prevent double-speed due to dual controls
}

void UTankMovementComponent::IntendMoveLeft(float Throw) {
	//UE_LOG(LogTemp, Warning, TEXT("%s: %f"), *Name, Throttle);
	//UE_LOG(LogTemp, Warning, TEXT("Intend move forward %f"), Throw)
	if (!LeftTrack || !RightTrack)
		return;
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);

	//TODO: prevent double-speed due to dual controls
}


