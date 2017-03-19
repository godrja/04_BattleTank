// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController();
	auto Pawn = PlayerController->GetPawn();
	return Cast<ATank>(Pawn);
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI: Player tank not found."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI: Player tank is: %s."), *(PlayerTank->GetName()));
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	AimTowardsPlayerTank();
}

void ATankAIController::AimTowardsPlayerTank()
{
	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank) { return; }
	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank) { return; }

	// Move towards the player
	
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	// Fire if ready
}

