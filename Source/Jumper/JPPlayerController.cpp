// Fill out your copyright notice in the Description page of Project Settings.

#include "JPPlayerController.h"
#include "JPGamePlayWidget.h"

AJPPlayerController::AJPPlayerController()
{
	static ConstructorHelpers::FClassFinder<UJPGamePlayWidget> JP_MENU_C(TEXT("/Game/Save/Widget/JPMenu.JPMenu_C"));
	if (JP_MENU_C.Succeeded())
	{
		MenuWidgetClass = JP_MENU_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UJPGamePlayWidget> JP_Result_MENU_C(TEXT("/Game/Save/Widget/JPResultMenu.JPResultMenu_C"));
	if (JP_Result_MENU_C.Succeeded())
	{
		ResultWidgetClass = JP_Result_MENU_C.Class;
	}
}

void AJPPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AJPPlayerController::Possess(APawn *aPawn)
{
	Super::Possess(aPawn);
}

void AJPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	ResultWidget = CreateWidget<UJPGamePlayWidget>(this, ResultWidgetClass);
}

void AJPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &AJPPlayerController::OnGamePause);
}

void AJPPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor = true;
	}
}

void AJPPlayerController::ShowResultUI()
{
	ResultWidget->AddToViewport();

	SetPause(true);
	ChangeInputMode(false);
}

void AJPPlayerController::OnGamePause()
{
	MenuWidget = CreateWidget<UJPGamePlayWidget>(this, MenuWidgetClass);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}


