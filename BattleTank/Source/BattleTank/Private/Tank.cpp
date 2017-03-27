// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::SetBarrelReference(UTankBarrel * ReferenceToSet)
{
	TankAimingComponent->SetBarrelReference(ReferenceToSet);
	Barrel = ReferenceToSet;
}

void ATank::SetTurretReference(UTankTurret * ReferenceToSet)
{
	TankAimingComponent->SetTurretReference(ReferenceToSet);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("ATank::Fire() called"));

	if (!Barrel) { return; }

	AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>
	(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
	);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}
