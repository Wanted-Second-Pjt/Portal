// Fill out your copyright notice in the Description page of Project Settings.


#include "Kang/PortalGameInstance.h"

#include "Kang/PortalMenuMode.h"
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

void UPortalGameInstance::TogglePauseGame()
{
	if (GetWorld()->GetAuthGameMode()->IsA(APortalMenuMode::StaticClass()))
	{
		return;
	}
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!MenuWidget)
	{
		MenuWidget = Cast<UPortalPauseWidget>(CreateWidget(PC, MenuWidgetFactory));
	}

	if (MenuWidget)
	{
	if (MenuWidget->IsInViewport())
	{
		MenuWidget->RemoveFromParent();
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
	}
	else
	{
		MenuWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		PC->bShowMouseCursor = true;
		FInputModeGameAndUI InputMode;
		InputMode.SetWidgetToFocus(MenuWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PC->SetInputMode(InputMode);
	}}
}



/*
void UPortalGameInstance::PauseGame()
{
	/*MenuWidget = CreateWidget<UPortalPauseWidget>(this, MenuWidgetFactory);
	MenuWidget->AddToViewport();#1#
	
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());
	}

}

void UPortalGameInstance::ContinueGame()
{
	/*
	MenuWidget->RemoveFromParent();
	#1#
	
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeGameOnly());
	}

	
}*/

void UPortalGameInstance::StartGame()
{
	CurrentLevel = 1;
	LoadGame(CurrentLevel);
}

void UPortalGameInstance::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}