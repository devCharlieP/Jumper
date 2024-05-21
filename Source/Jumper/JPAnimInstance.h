// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Jumper.h"
#include "Animation/AnimInstance.h"
#include "JPAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class JUMPER_API UJPAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UJPAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing", Meta = (AllowPrivateAccess = true))
	bool bIsClimbing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing", Meta = (AllowPrivateAccess = true))
	bool bIsClimbingUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing", Meta = (AllowPrivateAccess = true))
	bool bIsClimbingDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing", Meta = (AllowPrivateAccess = true))
	bool bIsClimbingLeft;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing", Meta = (AllowPrivateAccess = true))
	bool bIsClimbingRight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Climbing", Meta = (AllowPrivateAccess = true))
	bool bIsOnCeiling;
};
