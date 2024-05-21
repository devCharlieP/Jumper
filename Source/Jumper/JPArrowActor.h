// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Jumper.h"
#include "GameFramework/Actor.h"
#include "JPArrowActor.generated.h"

UCLASS()
class JUMPER_API AJPArrowActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJPArrowActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* ArrowComponent;
	
};
