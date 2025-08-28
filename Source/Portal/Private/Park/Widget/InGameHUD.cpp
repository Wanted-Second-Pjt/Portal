// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Widget/InGameHUD.h"
#include "Park/Widget/InGameWidget.h"
#include "Park/Player/PlayerCharacter.h"

AInGameHUD::AInGameHUD()
{
	ConstructorHelpers::FClassFinder<UInGameWidget> TempAimWidget(TEXT("/Game/Park/UI/WBP_InGame.WBP_InGame_C"));
	if (TempAimWidget.Succeeded())
	{
		AimWidgetFactory = TempAimWidget.Class;
	}
}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (UInGameWidget* AimWidget = CreateWidget<UInGameWidget>(GetWorld(), AimWidgetFactory, "InGameWidget"))
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(PC->GetPawn());
			if (IsValid(Player))
			{
				Player->GetPortalComp()->SetAimWidget(AimWidget);
			}
		}
	}
}
