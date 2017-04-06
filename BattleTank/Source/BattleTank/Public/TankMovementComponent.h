// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Handles movement of tracks
 */
UCLASS(ClassGroup = (Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendMoveForward(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendTurnRight(float Throw);

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;

};
