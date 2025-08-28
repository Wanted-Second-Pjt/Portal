// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PORTAL_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

protected:
	AInGameHUD();
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UInGameWidget> AimWidgetFactory;
};
