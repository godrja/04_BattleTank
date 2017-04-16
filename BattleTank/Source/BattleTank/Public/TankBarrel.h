// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Holds barrel's properties, and custom actions like Elevate.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1.0 for max downward speed, +1.0 for max upward speed
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 15; // Sensible default

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 30; // Sensible default

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = -0.45; // Sensible default

};
