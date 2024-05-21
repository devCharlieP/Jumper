// Fill out your copyright notice in the Description page of Project Settings.

#include "JPArrowActor.h"
#include "Components/ArrowComponent.h"

// Sets default values
AJPArrowActor::AJPArrowActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	RootComponent = ArrowComponent;

	ArrowComponent->bHiddenInGame = false;
}

// Called when the game starts or when spawned
void AJPArrowActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJPArrowActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

