// Fill out your copyright notice in the Description page of Project Settings.


#include "Kang/PortalMenuUserWidget.h"

#include "Components/Button.h"
#include "Kang/PortalGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"



void UPortalMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	/*
	RestartButton->OnClicked.AddDynamic(this, &UPortalMenuUserWidget::Restart);
	ContinueButton->OnClicked.AddDynamic(this, &UPortalMenuUserWidget::Continue);
	*/
	

}
