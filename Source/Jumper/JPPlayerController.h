// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Jumper.h"
#include "GameFramework/PlayerController.h"
#include "JPPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JUMPER_API AJPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AJPPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void Possess(APawn* aPawn) override;	

	void ChangeInputMode(bool bGameMode = true);

	void ShowResultUI();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UJPGamePlayWidget> MenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UJPGamePlayWidget> ResultWidgetClass;

private:
	void OnGamePause();

	UPROPERTY()
	class UJPGamePlayWidget* MenuWidget;

	UPROPERTY()
	class UJPGamePlayWidget* ResultWidget;

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UIInputMode;
};
