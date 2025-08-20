// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PortalMenuMode.generated.h"

/**
 * 
 */
UCLASS()
class PORTAL_API APortalMenuMode : public AGameModeBase
{
	GENERATED_BODY()

	
public:
	APortalMenuMode();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPortalMenuUserWidget> PortalMenuUserWidgetClass;

	UPROPERTY()
	class UPortalMenuUserWidget* MenuWidgetInstance;

};
