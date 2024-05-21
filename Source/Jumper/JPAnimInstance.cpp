// Fill out your copyright notice in the Description page of Project Settings.

#include "JPAnimInstance.h"
#include "JPCharacter.h"

UJPAnimInstance::UJPAnimInstance()
{
	IsInAir = false;
	CurrentPawnSpeed = 0.0f;
	bIsClimbing = false;
	bIsOnCeiling = false;
}

void UJPAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		auto Character = Cast<AJPCharacter>(Pawn);

		if (Character)
		{
			IsInAir = Character->GetMovementComponent()->IsFalling();
			CurrentWalkSpeed = Character->GetMovementComponent()->GetMaxSpeed();
			
			bIsClimbing = Character->bIsClimbing;

			bIsClimbingUp = Character->IsClimbingUp();
			bIsClimbingDown = Character->IsClimbingDown();
			bIsClimbingLeft = Character->IsClimbingLeft();
			bIsClimbingRight = Character->IsClimbingRight();

			bIsOnCeiling = Character->bIsOnCeiling;
		}
	}
}

