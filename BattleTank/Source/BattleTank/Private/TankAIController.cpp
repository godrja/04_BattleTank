// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	auto* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	// not ensure(PlayerTank) because it may be absent when the player has died
	if (!ensure(AimingComponent) || !PlayerTank) { return; }

	// Move towards the player
	MoveToActor(
		PlayerTank,
		AcceptanceRadius,
		true, // stop on overlap
		true, // use path-finding
		false // can strafe
	);
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!(ensure(PossessedTank))) { return; }

		PossessedTank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::WhenTankDied);
	}
}

void ATankAIController::WhenTankDied()
{
	APawn* MyPawn = GetPawn();

	if (MyPawn)
	{
		MyPawn->DetachFromControllerPendingDestroy();
	}
}

