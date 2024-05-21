// Fill out your copyright notice in the Description page of Project Settings.

#include "JPTextActor.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AJPTextActor::AJPTextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	RootComponent = TextRender;

	// Set the text to "start"
	TextRender->SetText(FText::FromString(TEXT("start")));
	TextRender->SetHorizontalAlignment(EHTA_Center);
	TextRender->SetWorldSize(100.0f);  // Set the size of the text
}

// Called when the game starts or when spawned
void AJPTextActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJPTextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

