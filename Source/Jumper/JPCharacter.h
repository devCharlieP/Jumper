// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Jumper.h"
#include "GameFramework/Character.h"
#include "JPCharacter.generated.h"

UCLASS()
class JUMPER_API AJPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJPCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetControlMode(int32 ControlMode);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool IsClimbingUp() const { return bIsClimbing && ClimbingDirectionUD > 0.0f; }
	bool IsClimbingDown() const { return bIsClimbing && ClimbingDirectionUD < 0.0f; }
	bool IsClimbingLeft() const { return bIsClimbing && ClimbingDirectionLR > 0.0f; }
	bool IsClimbingRight() const { return bIsClimbing && ClimbingDirectionLR < 0.0f; }

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Movement: Walking")
	float RunSpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ClimbingSpeed = 100.0f;  // 벽 오르기 속도

	float ClimbingDirectionUD;  // +1 for up, -1 for down
	float ClimbingDirectionLR;  // +1 for left, -1 for right

	bool bIsClimbing;
	bool bIsOnCeiling;
	bool bIsJump;

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	virtual void Jump() override;

	void Run();
	void StopRun();

	void CheckWallAndCeilingPresence();
	void ToggleClimbing();
	void StartClimbing();
	void StopClimbing();

	FVector WallNormal;
};
