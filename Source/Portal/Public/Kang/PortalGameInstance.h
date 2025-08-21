// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Park/RelatedPhysics/PortalGameMode.h"
#include "PortalPauseWidget.h"

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
	void LoadGame(int32 Level);

	UFUNCTION(BlueprintCallable)
	void PauseGame();

	UFUNCTION(BlueprintCallable)
	void ContinueGame();

	UFUNCTION(BlueprintCallable)
	void StartGame();

	UFUNCTION(BlueprintCallable)
	void QuitGame();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentLevel;

	
	UPROPERTY()
	UPortalPauseWidget* MenuWidget;

};
