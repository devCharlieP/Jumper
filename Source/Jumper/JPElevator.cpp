// Fill out your copyright notice in the Description page of Project Settings.

#include "JPElevator.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "TimerManager.h"


// Sets default values
AJPElevator::AJPElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	RootComponent = PlatformMesh;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/Save/Actor/EleavatorCurveBase.EleavatorCurveBase"));
	if (Curve.Succeeded())
	{
		MovementCurve = Curve.Object;
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/SoulCity/Merged/SM_MERGED_SM_Slums_Floor_01.SM_MERGED_SM_Slums_Floor_01"));
	if (Mesh.Succeeded())
	{
		StaticMesh = Mesh.Object;
		PlatformMesh->SetStaticMesh(StaticMesh);
	}
}

// Called when the game starts or when spawned
void AJPElevator::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
	EndLocation = StartLocation + FVector(0, 0, 1000); // 500 units up

	if (MovementCurve)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("OnTimelineUpdate"));

		FOnTimelineEvent TimelineFinished;
		TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));

		MoveTimeline.AddInterpFloat(MovementCurve, ProgressFunction);
		MoveTimeline.SetTimelineFinishedFunc(TimelineFinished);
		MoveTimeline.SetLooping(false);

		// ó���� �÷����� �̵���Ű�� ���� Ÿ�̸� ����
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AJPElevator::MovePlatform, 1.0f, false);
	}
}

// Called every frame
void AJPElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTimeline.TickTimeline(DeltaTime);
}

void AJPElevator::OnTimelineUpdate(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Value);
	SetActorLocation(NewLocation);
}

void AJPElevator::OnTimelineFinished()
{
	// Ÿ�Ӷ����� ���� ������ �ݴ� �������� �̵�
	if (MoveTimeline.GetPlaybackPosition() == 0.0f)
	{
		MoveTimeline.Play();
	}
	else
	{
		MoveTimeline.Reverse();
	}

	// ���� �ð� �Ŀ� �÷����� �ٽ� �̵���Ű�� ���� Ÿ�̸� ����
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AJPElevator::MovePlatform, 10.0f, false);
}

void AJPElevator::MovePlatform()
{
	if (MoveTimeline.IsReversing() || MoveTimeline.GetPlaybackPosition() == 0.0f)
	{
		MoveTimeline.Play();
	}
	else
	{
		MoveTimeline.Reverse();
	}
}
