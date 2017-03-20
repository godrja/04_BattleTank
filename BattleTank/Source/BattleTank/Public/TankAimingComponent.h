// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void SetBarrelReference(UTankBarrel* ReferenceToSet);

	void SetTurretReference(UTankTurret* ReferenceToSet);

	void AimAt(FVector WorldSpaceAim, float LaunchSpeed);
	
	void MoveBarrelTowards(FVector AimDirection);

	void RotateTurretTowards(FVector AimDirection);

private:
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

};
