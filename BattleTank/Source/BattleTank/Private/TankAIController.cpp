// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"


void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	auto* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(AimingComponent && PlayerTank)) { return; }

	// Move towards the player
	MoveToActor(
		PlayerTank, 
		AcceptanceRadius, 
		true, // stop on overlap
		true, // use path-finding
		false // can strafe
	);
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	
	// TODO: Fix firing
	//ControlledTank->Fire();
}

