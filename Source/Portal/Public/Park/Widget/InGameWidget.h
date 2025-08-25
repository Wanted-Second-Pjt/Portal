// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kang/PortalMenuUserWidget.h"
#include "InGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTAL_API UInGameWidget : public UPortalMenuUserWidget
{
	GENERATED_BODY()

public:
	void SetEnableBlue(bool bEnable);
	void SetEnableOrange(bool bEnable);
};
