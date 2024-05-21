// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Jumper.h"
#include "GameFramework/GameModeBase.h"
#include "JPGameMode.generated.h"

/**
 * 
 */
UCLASS()
class JUMPER_API AJPGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AJPGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
};
