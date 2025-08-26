// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class PORTAL_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetEnableBlue(const bool& bEnable) const;
	void SetEnableOrange(const bool& bEnable) const;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UImage* BlueAim;
	UPROPERTY(meta=(BindWidget))
	UImage* OrangeAim;
};
