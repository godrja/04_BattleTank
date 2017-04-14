// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ensure(PlayerTank)) { return; }

	ATank* ControlledTank = Cast<ATank>(GetPawn());
	if (!ensure(ControlledTank)) { return; }

	// Move towards the player
	MoveToActor(
		PlayerTank, 
		AcceptanceRadius, 
		true, // stop on overlap
		true, // use path-finding
		false // can strafe
	);
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire();
}

