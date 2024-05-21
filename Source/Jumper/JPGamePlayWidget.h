// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Jumper.h"
#include "Blueprint/UserWidget.h"
#include "JPGamePlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class JUMPER_API UJPGamePlayWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnResumeClicked();

	UFUNCTION()
	void OnReturnToTitleClicked();

	UFUNCTION()
	void OnRetryGameClicked();

protected:
	UPROPERTY()
	class UButton* ResumeButton;

	UPROPERTY()
	class UButton* ReturnToTitleButton;
	
	UPROPERTY()
	class UButton* RetryGameButton;
};
