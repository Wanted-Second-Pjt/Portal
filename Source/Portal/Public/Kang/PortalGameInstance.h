// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Park/RelatedPhysics/PortalGameMode.h"
#include "PortalGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTAL_API UPortalGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadGame();
	
};
