// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Jumper.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "JPElevator.generated.h"

UCLASS()
class JUMPER_API AJPElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJPElevator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
	UCurveFloat* MovementCurve;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMesh* StaticMesh;

	FVector StartLocation;
	FVector EndLocation;

	FTimeline MoveTimeline;
	FTimerHandle TimerHandle;

	UFUNCTION()
	void OnTimelineUpdate(float Value);

	UFUNCTION()
	void OnTimelineFinished();

	void MovePlatform();
};
