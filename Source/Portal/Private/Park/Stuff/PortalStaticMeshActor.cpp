// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Stuff/PortalStaticMeshActor.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Park/Player/PlayerCharacter.h"

FVector PortalExtent = FVector();

// Sets default values
APortalStaticMeshActor::APortalStaticMeshActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
}

void APortalStaticMeshActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if ((GetWorld() && GetWorld()->HasBegunPlay()) == false)
	{
		return;
	}

	//ReadWorldStatus();
}

void APortalStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
	//if (FixedInversedRotationScaleMatrix == FMatrix(ForceInit))
		//ReadWorldStatus();
}


bool APortalStaticMeshActor::Respond(const FHitResult& HitInfo, AActor* Portal)
{
	if (!IsValid(GetStaticMeshComponent()->GetStaticMesh()))
	{return false;}
	static FVector PortalExtent =
		Portal->GetComponentByClass<UStaticMeshComponent>()
		->GetStaticMesh()->GetBounds().BoxExtent;
	FVector ModifiedLocation = ModifyIfPortalCanMake(HitInfo, FVector2D(PortalExtent.X, PortalExtent.Y));
	//if (ModifiedLocation == FVector::ZeroVector)
	//{return false;}

	UArrowComponent* PortalArrow = Portal->GetComponentByClass<UArrowComponent>();
	FVector PortalDirection = PortalArrow->GetForwardVector();
	FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(PortalDirection, HitInfo.ImpactNormal);
	FMinimalViewInfo ViewInfo;
	APlayerCharacter* Player = CastChecked<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetOwner());

	// Camera의 방향과 맞추기 In Beta
	float Angle = HitInfo.ImpactNormal.Cross(GetActorRightVector()).Dot(PortalArrow->GetUpVector());
	NewRotation.Yaw(Angle);
	Portal->SetActorLocationAndRotation(ModifiedLocation, NewRotation);
	// Portal->Activate After Portal Cpp Class In Beta
	return true; 
}

void APortalStaticMeshActor::ReadWorldStatus()
{	
	FTransform ActorTransform = GetActorTransform();
	FQuat FixedInversedRotationMatrix = ActorTransform.GetRotation().Inverse();
	
	FixedInversedScaleMatrix = FScaleMatrix(FVector(1.0f) / ActorTransform.GetScale3D());
	FixedInversedRotationScaleMatrix = FMatrix::Identity;
	FixedInversedRotationScaleMatrix = FQuatRotationMatrix(FixedInversedRotationMatrix) * FixedInversedScaleMatrix;

	FVector ToForwardPointVector = GetStaticMeshComponent()->Bounds.BoxExtent - GetActorLocation();
	DegreeToPointInForwardSurface = GetActorForwardVector().Dot(ToForwardPointVector.GetSafeNormal());
}

FVector APortalStaticMeshActor::ModifyIfPortalCanMake(const FHitResult& HitInfo, const FVector2D& Extent, float Tolerance) const
{
	//if (FixedInversedRotationScaleMatrix == FMatrix(ForceInit))
	//{return FVector();}
	//FVector PointToThisCoordinate = HitInfo.Location - GetActorLocation();
	//FVector ToLocalTransform = FixedInversedRotationScaleMatrix.TransformPosition(PointToThisCoordinate);
	FVector RetLocation = FVector();
	if (HitInfo.ImpactNormal.Dot(GetActorForwardVector()) < 0.001f)
	{}
	else if (HitInfo.ImpactNormal.Dot(GetActorUpVector()) < 0.001f)
	{}
	else if (HitInfo.ImpactNormal.Dot(GetActorRightVector()) < 0.001f)
	{}
	
	return HitInfo.ImpactNormal;// to RetLocation In Beta
}

