// Fill out your copyright notice in the Description page of Project Settings.

#include "JPFinish.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "JPPlayerController.h"

// Sets default values
AJPFinish::AJPFinish()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));	
	RootComponent = TriggerBox;

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AJPFinish::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AJPFinish::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJPFinish::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJPFinish::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		AJPPlayerController* PlayerController = Cast<AJPPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
		if (PlayerController)
		{
			PlayerController->ShowResultUI();
		}
	}
}