// Fill out your copyright notice in the Description page of Project Settings.


#include "Kang/PortalMenuUserWidget.h"

#include "Components/Button.h"
#include "Kang/PortalGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"



void UPortalMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UPortalMenuUserWidget::StartGame);

	QuitButton->OnClicked.AddDynamic(this, &UPortalMenuUserWidget::QuitGame);

	
	/*
	RestartButton->OnClicked.AddDynamic(this, &UPortalMenuUserWidget::Restart);
	ContinueButton->OnClicked.AddDynamic(this, &UPortalMenuUserWidget::Continue);
	*/
	

}

void UPortalMenuUserWidget::StartGame()
{
	if (UPortalGameInstance* GameInstance = GetGameInstance<UPortalGameInstance>())
	{
		GameInstance->LoadGame();
	}
}

void UPortalMenuUserWidget::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

