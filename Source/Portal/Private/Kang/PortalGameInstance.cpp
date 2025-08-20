// Fill out your copyright notice in the Description page of Project Settings.


#include "Kang/PortalGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UPortalGameInstance::LoadMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MenuMap"), true);
}

void UPortalGameInstance::LoadGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("GameMap"), true);
	UGameplayStatics::
}
