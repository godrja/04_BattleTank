// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Determine the find pitch angle based on the AimDirection
	// Change the barren pitch angle to make it closer to the desired value based on the delta seconds
	auto Time = GetWorld()->GetTimeSeconds();

	UE_LOG(LogTemp, Warning, TEXT("%f: UTankBarrel::Elevate() called"), Time);
}


