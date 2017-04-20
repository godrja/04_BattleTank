// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	// Do it here to make sure that StartingHealth has been set in the blueprint
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 ActualDamage = FMath::Clamp(FPlatformMath::RoundToInt(Damage), 0, CurrentHealth);
	CurrentHealth -= ActualDamage;

	if (!CurrentHealth)
	{
		OnTankDeath.Broadcast();
	}

	return ActualDamage;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}
