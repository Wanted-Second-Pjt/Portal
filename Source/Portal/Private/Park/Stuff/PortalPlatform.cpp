// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Stuff/PortalPlatform.h"

#include "Utility/Helper.h"
#include "Kismet/GameplayStatics.h"

UStaticMeshComponent* APortalPlatform::PortalMesh = nullptr;
const float APortalPlatform::SurfaceTolerance = 0.9f;

// Sets default values
APortalPlatform::APortalPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	APortalPlatform::PortalMesh = Helper::GetPortalFromConstructor()->GetComponentByClass<UStaticMeshComponent>();
	
}

bool APortalPlatform::CanPlacePortal(const FVector& HitLocation, const FVector& SurfaceNormal)
{
	FVector AbsNormal = SurfaceNormal.GetAbs();
	(PortalMesh->GetComponentTransform().ToMatrixWithScale() * FixedInversedRotationScaleMatrix);
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	if (AbsNormal.Dot(GetActorForwardVector()) > 0.9f)
	{
	}
	if (AbsNormal.Dot(GetActorRightVector()) > 0.9f)
	{
	}
	if (AbsNormal.Dot(GetActorUpVector()) > 0.9f)
	{
	}
	return false;
}

void APortalPlatform::SetEntrance(const bool& CanEnter) const
{
	CanEnter ?
		MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore) :
		MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

// Called when the game starts or when spawned
void APortalPlatform::BeginPlay()
{
	Super::BeginPlay();
	ReadInversedSRTMatrix();
}

void APortalPlatform::ReadInversedSRTMatrix()
{
	FTransform ActorTransform = GetActorTransform();
	FixedInversedRotationMatrix = FQuatRotationMatrix(ActorTransform.GetRotation().Inverse());
	FMatrix FixedInversedScaleMatrix = FScaleMatrix(FVector(1.0f) / ActorTransform.GetScale3D());
	
	FixedInversedRotationScaleMatrix = FixedInversedRotationMatrix * FixedInversedScaleMatrix;
}

/*
// Called every frame
void APortalPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
*/
