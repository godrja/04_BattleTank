// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank not found."));
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled tank: %s."), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		ControlledTank->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	HitLocation = FVector(1.0);

	// Determine the screen location of the crosshair
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D
	(
			ViewportSizeX * CrosshairXLocation,
			ViewportSizeY * CrosshairYLocation
	);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		if (GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
			return true;
		} 
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Nothing has been hit"));
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X,
		ScreenLocation.Y,
		WorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector Start = GetPlayerLocation();
	FVector End = Start + LookDirection * 10000;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		UE_LOG(LogTemp, Warning, TEXT("Object hit is: %s"), *HitResult.GetActor()->GetName());
		return true;
	}
	else
	{
		HitLocation = FVector(0.0);
		return false;
	}
}

FVector ATankPlayerController::GetPlayerLocation() const
{
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetPlayerViewPoint(PlayerLocation, PlayerRotation);
	// Also coult you PlayerCameraManager->GetCameraLocation()
	return PlayerLocation;
}
