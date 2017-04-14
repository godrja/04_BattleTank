// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	// Start the tank moving the barrel so that a shot would hit 
	// where the crosshair intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	// Relative horizontal position of the crosshair at the viewport
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;

	// Relative vertical position of the crosshair at the viewport
	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333;

	// Maximum length of aiming
	UPROPERTY(EditDefaultsOnly)
	int32 LineTraceRange = 1000000; // 10 km

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	FVector GetPlayerLocation() const;
};
