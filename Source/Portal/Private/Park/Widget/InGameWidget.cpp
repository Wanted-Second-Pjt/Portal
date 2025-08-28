// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Widget/InGameWidget.h"
#include "Components/Image.h"

void UInGameWidget::SetEnableBlue(const bool& bEnable) const
{
	BlueAim->SetOpacity(bEnable);
	
}

void UInGameWidget::SetEnableOrange(const bool& bEnable) const
{
	OrangeAim->SetOpacity(bEnable);
}
