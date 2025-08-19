// Fill out your copyright notice in the Description page of Project Settings.


#include "Kang/PortalMenuUserWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UPortalMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	QuitButton->OnClicked.AddDynamic(this, &UPortalMenuUserWidget::Quit);

	
	/*
	StartButton->OnClicked.AddDynamic(this, &UPortalMenuUserWidget::Start);
	RestartButton->OnClicked.AddDynamic(this, &UPortalMenuUserWidget::Restart);
	ContinueButton->OnClicked.AddDynamic(this, &UPortalMenuUserWidget::Continue);
	*/
	


	
}

void UPortalMenuUserWidget::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}
