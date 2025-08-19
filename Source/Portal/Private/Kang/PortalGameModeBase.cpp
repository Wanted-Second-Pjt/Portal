// Fill out your copyright notice in the Description page of Project Settings.


#include "Kang/PortalGameModeBase.h"
#include "Kang/PortalMenuUserWidget.h"
#include "Components/textblock.h"
#include "Kismet/GameplayStatics.h"

void APortalGameModeBase::BeginPlay()
{}
void APortalGameModeBase::ShowMenu()
{
	if (MenuWidget != nullptr)
	{
		MenuUI = CreateWidget<UPortalMenuUserWidget>(GetWorld(), MenuWidget);
		if (MenuUI != nullptr)
		{
			MenuUI->AddToViewport();

			UGameplayStatics::SetGamePaused(GetWorld(), true);

			GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
		}
		
	}
}


