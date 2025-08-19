// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PortalGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PORTAL_API APortalGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPortalMenuUserWidget> MenuWidget;

public:
	void ShowMenu();
	void HideMenu();

protected:
	virtual void BeginPlay() override;

private:
	UPortalMenuUserWidget* MenuUI;
};
