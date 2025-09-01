// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/SceneComponents/PortalComponent.h"

#include "MovieSceneFwd.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "Park/Widget/InGameWidget.h"
#include "Park/Stuff/PortalPlatform.h"
#include "Kang/PortalPortal.h"


UPortalComponent::UPortalComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Params.AddIgnoredActor(GetOwner());
	//Params.TraceTag = 
}
	
void UPortalComponent::BeginPlay()
{
	Super::BeginPlay();
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner());
	if (!IsValid(Player))
	{
		return;
	}
	TArray<AActor*> Portals;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Portal", Portals);
	for (AActor* Iter : Portals)
	{
		APortalPortal* Portal = Cast<APortalPortal>(Iter);
		if (!IsValid(Portal))
		{
			continue;
		}
		
		Portal->PortalCamera->ShowOnlyComponents.Add(Player->GetMesh());
		Portal->PortalCamera->HideComponent(Player->GetVisibleMeshComp());
		Portal->ActorHasTag("Blue") ?
			BluePortal = Portal : OrangePortal = Portal;
		
	}
	AimWidget->AddToViewport(0);
}

bool UPortalComponent::GetHitResultFromPlatform(const FVector& StartPos, const FVector& Direction, float TraceDistance)
{

	if (!HasPortalGun)
	{
		if (IsValid(AimWidget))
		{
			AimWidget->SetEnableOrange(false);
			AimWidget->SetEnableBlue(false);
		}
		return false;
	}
	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartPos,
		StartPos + Direction * TraceDistance,
		ECC_Visibility,
		Params
	);

	if (APortalPlatform* Platform = Cast<APortalPlatform>(HitResult.GetActor());
		bHit && IsValid(Platform))
	{
		const bool bCanPlace = Platform->CanPlacePortal(HitResult.ImpactPoint, HitResult.ImpactNormal);
		if (IsValid(AimWidget))
		{
			AimWidget->SetEnableOrange(bCanPlace);
			AimWidget->SetEnableBlue(bCanPlace);
		}
		return bCanPlace;
	}
	if (IsValid(AimWidget))
	{
		AimWidget->SetEnableOrange(false);
		AimWidget->SetEnableBlue(false);
	}
	return false;
}


