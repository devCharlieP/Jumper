// Fill out your copyright notice in the Description page of Project Settings.

#include "JPGameMode.h"
#include "JPCharacter.h"
#include "JPPlayerController.h"

AJPGameMode::AJPGameMode()
{
	DefaultPawnClass = AJPCharacter::StaticClass();
	PlayerControllerClass = AJPPlayerController::StaticClass();
}

void AJPGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

