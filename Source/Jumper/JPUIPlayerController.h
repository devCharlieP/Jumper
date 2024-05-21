// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Jumper.h"
#include "GameFramework/PlayerController.h"
#include "JPUIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JUMPER_API AJPUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UUserWidget> UIWidgetClass;
	
	UPROPERTY()
	class UUserWidget* UIWidgetInstance;
	
};
