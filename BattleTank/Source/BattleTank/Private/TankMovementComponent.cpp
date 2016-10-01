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

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	//No need to call super as we replacing the method
	//auto TankName = GetOwner()->GetName();
	auto TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal(); //the safe method don't change the vector MoveVelocity
	//UE_LOG(LogTemp, Warning, TEXT("Tank: %s vectoring to %s"), *TankName, *MoveVelocityString);
	
	//World Coordinates
	auto FowardThrow = FVector::DotProduct(TankForwardDirection, AIForwardIntention);
	IntendMoveForward(FowardThrow);
	
	auto RightThrow = FVector::CrossProduct(TankForwardDirection, AIForwardIntention).Z;
	IntendMoveRight(RightThrow);
}


