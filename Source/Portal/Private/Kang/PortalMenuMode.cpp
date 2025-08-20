// Fill out your copyright notice in the Description page of Project Settings.


#include "Kang/PortalMenuMode.h"
#include "Kang/PortalMenuUserWidget.h"
#include "Components/textblock.h"
#include "Kismet/GameplayStatics.h"

APortalMenuMode::APortalMenuMode()
{
	// Find the PortalMenuUserWidget Blueprint (set correct path!)
	static ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Kang/GameMode/WBP_PortalMenuUserWidget.WBP_PortalMenuUserWidget_C'"));
	if (MenuBPClass.Succeeded())
	{
		PortalMenuUserWidgetClass = MenuBPClass.Class;
	}

	// No pawn in main menu
	DefaultPawnClass = nullptr;
}


void APortalMenuMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PortalGameModeBase::BeginPlay called"));

	//if (MenuWidgetClass)
	{
		MenuWidgetInstance = CreateWidget<UPortalMenuUserWidget>(GetWorld(), PortalMenuUserWidgetClass);
	//	if (MenuWidgetInstance)
		{
			MenuWidgetInstance->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("Menu widget created and added to viewport"));


			if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
			{
				PC->bShowMouseCursor = true;
				PC->SetInputMode(FInputModeUIOnly());
			}
		}
	}
}