// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PortalMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTAL_API UPortalMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	class UPortalMenuUserWidget* MenuUserWidget;*/
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* QuitButton;

	/*UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* RestartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ContinueButton;*/

protected:
	virtual void NativeConstruct() override;

private:
	
	//UFUNCTION()
	//void Restart();
	//
	//UFUNCTION()
	//void Continue();
};
