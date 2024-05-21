// Fill out your copyright notice in the Description page of Project Settings.

#include "JPGamePlayWidget.h"
#include "Components/Button.h"
#include "JPPlayerController.h"

void UJPGamePlayWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton = Cast<UButton>(GetWidgetFromName(TEXT("btnResume")));
	if (nullptr != ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UJPGamePlayWidget::OnResumeClicked);
	}

	ReturnToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnReturnToTitle")));
	if (nullptr != ReturnToTitleButton)
	{
		ReturnToTitleButton->OnClicked.AddDynamic(this, &UJPGamePlayWidget::OnReturnToTitleClicked);
	}

	RetryGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnRetryGame")));
	if (nullptr != RetryGameButton)
	{
		RetryGameButton->OnClicked.AddDynamic(this, &UJPGamePlayWidget::OnRetryGameClicked);
	}
}

void UJPGamePlayWidget::OnResumeClicked()
{
	auto JPPlayerController = Cast<AJPPlayerController>(GetOwningPlayer());

	RemoveFromParent();

	JPPlayerController->ChangeInputMode(true);
	JPPlayerController->SetPause(false);
}

void UJPGamePlayWidget::OnReturnToTitleClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}

void UJPGamePlayWidget::OnRetryGameClicked()
{
	auto JPPlayerController = Cast<AJPPlayerController>(GetOwningPlayer());
	JPPlayerController->RestartLevel();
}



