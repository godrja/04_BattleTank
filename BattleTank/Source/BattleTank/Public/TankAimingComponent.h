// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	Reloading, 
	Aiming, 
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void SetBarrelReference(UTankBarrel* ReferenceToSet);

	void SetTurretReference(UTankTurret* ReferenceToSet);

	void AimAt(FVector WorldSpaceAim);

	void MoveBarrelTowards(FVector AimDirection);

	void RotateTurretTowards(FVector AimDirection);

	UFUNCTION(BlueprintCallable, Category = Control)
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Locked;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	double LastFireTime = 0;

};