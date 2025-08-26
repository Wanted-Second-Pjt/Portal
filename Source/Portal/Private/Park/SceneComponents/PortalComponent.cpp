// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/SceneComponents/PortalComponent.h"

#include "MovieSceneFwd.h"
#include "Park/Widget/InGameWidget.h"
#include "Park/Stuff/PortalPlatform.h"
//#include "Park/"


UPortalComponent::UPortalComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Params.AddIgnoredActor(GetOwner());

	
	AimWidget = CreateWidget<UInGameWidget>(Cast<APlayerController>(GetOwner()->GetInstigatorController()), UInGameWidget::StaticClass(), "AimWidget");
}

void UPortalComponent::BeginPlay()
{
	Super::BeginPlay();
	AimWidget->AddToPlayerScreen();
}

bool UPortalComponent::GetHitResultFromPlatform(const FVector& StartPos, const FVector& EndPos, float TraceDistance)
{
	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartPos,
		EndPos,
		ECC_Visibility,
		Params
	);

	if (APortalPlatform* Platform = Cast<APortalPlatform>(HitResult.GetActor());
		bHit && IsValid(Platform))
	{
		const bool bCanPlace = Platform->CanPlacePortal(HitResult.ImpactPoint, HitResult.ImpactNormal);
		AimWidget->SetEnableOrange(bCanPlace);
		AimWidget->SetEnableBlue(bCanPlace);
		return bCanPlace;
	}
	
	AimWidget->SetEnableOrange(false);
	AimWidget->SetEnableBlue(false);
	return false;
}


