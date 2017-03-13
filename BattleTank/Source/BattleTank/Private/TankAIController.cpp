// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"


// TODO: Remove me plis
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


