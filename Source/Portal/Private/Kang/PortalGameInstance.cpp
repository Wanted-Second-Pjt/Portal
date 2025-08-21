// Fill out your copyright notice in the Description page of Project Settings.


#include "Kang/PortalGameInstance.h"
#include "Kang/PortalPauseWidget.h"
#include "Kismet/GameplayStatics.h"


void UPortalGameInstance::LoadMenu()
{
	CurrentLevel = 0;
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MenuMap"), true);
}

void UPortalGameInstance::LoadGame(int32 Level)
{
	FString MapName = FString::Printf(TEXT("GameMap%d"), Level);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName), true);
	CurrentLevel = Level;

}

void UPortalGameInstance::PauseGame()
{
	MenuWidget->AddToViewport();
	UGameplayStatics::SetGamePaused(GetWorld(), true);

}

void UPortalGameInstance::ContinueGame()
{
	MenuWidget->RemoveFromViewport();
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	
}

void UPortalGameInstance::StartGame()
{
	CurrentLevel = 1;
	LoadGame(CurrentLevel);
}

void UPortalGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}