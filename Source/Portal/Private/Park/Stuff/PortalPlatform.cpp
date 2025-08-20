// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Stuff/PortalPlatform.h"

#include "Components/ArrowComponent.h"
#include "Utility/Helper.h"
#include "Kismet/GameplayStatics.h"

TObjectPtr<AActor> APortalPlatform::Portal = nullptr;
const float APortalPlatform::SurfaceTolerance = 0.9f;

// Sets default values
APortalPlatform::APortalPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

bool APortalPlatform::CanPlacePortal(const FVector& HitLocation, const FVector& SurfaceNormal)
{
	static const UStaticMeshComponent* PortalMeshComp = Portal->GetComponentByClass<UStaticMeshComponent>();
	static const UArrowComponent* PortalArrowComp = Portal->GetComponentByClass<UArrowComponent>();
	static FTransform WorldPortal = PortalMeshComp->GetComponentTransform();
	FVector CamRightVector = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorRightVector();
	// Hit Surface
	const FVector LocalNormal = InversedTransform.GetRotation() * SurfaceNormal;
	// to be Placed UpVector
	const FVector LocalPortalUpVector = InversedTransform.GetRotation() * CamRightVector.Cross(SurfaceNormal);
	FVector Min, Max;
	PortalMeshComp->GetLocalBounds(Min, Max);
	
	
	
	if (LocalNormal.Dot(GetActorForwardVector()) > 0.9f)
	{
	}
	if (LocalNormal.Dot(GetActorRightVector()) > 0.9f)
	{
	}
	if (LocalNormal.Dot(GetActorUpVector()) > 0.9f)
	{
	}
	return false;
}

void APortalPlatform::SetEntrance(const bool& CanEnter) const
{
	CanEnter ?
		MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore) :
		MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block)
	;
}

// Called when the game starts or when spawned
void APortalPlatform::BeginPlay()
{
	Super::BeginPlay();
	Portal = UGameplayStatics::GetActorOfClass(GetWorld(), Helper::GetPortalClassFromConstructor());
	InversedTransform = GetTransform().Inverse();
}



/*
// Called every frame
void APortalPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
*/
