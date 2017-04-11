// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"




void UTankTrack::SetThrottle(float Throttle)
{
	// TODO: Clamp the actual throttle value so that players can't overdrive
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* RootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	RootComponent->AddForceAtLocation(ForceApplied, ForceLocation);
}
