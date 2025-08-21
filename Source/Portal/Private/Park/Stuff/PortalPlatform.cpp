// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Stuff/PortalPlatform.h"

#include "MatrixTypes.h"
#include "Algo/Includes.h"
#include "Components/ArrowComponent.h"
#include "Utility/Helper.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/DebugHelper.h"

TObjectPtr<AActor> APortalPlatform::Portal = nullptr;
const float APortalPlatform::EdgeMargin = 10.f;
const float APortalPlatform::SurfaceTolerance = 0.9f;

// Sets default values
APortalPlatform::APortalPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetMobility(EComponentMobility::Static);
	SetRootComponent(MeshComp);
	LocalBoxExtent = MeshComp->GetStaticMesh()->GetBoundingBox().GetExtent();
}

void APortalPlatform::BeginPlay()
{
	Super::BeginPlay();
	// 추후 cpp Portal 생기면 해당 class 가져오기
	Portal = UGameplayStatics::GetActorOfClass(GetWorld(), Helper::GetPortalClassFromConstructor());
	InversedTransform = GetTransform().Inverse();
}

void APortalPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//if () Player-Portal 일정 거리 이하로 오면
	//MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	//MeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

bool APortalPlatform::CanPlacePortal(const FVector& HitLocation, const FVector& HitNormal)
{
	if (Portal == nullptr)
	{
		return false;
	}
	
	static const UStaticMeshComponent* PortalMeshComp = Portal->GetComponentByClass<UStaticMeshComponent>();
	static FTransform WorldPortalTransform = PortalMeshComp->GetComponentTransform();
	static FVector PortalExtent = PortalMeshComp->GetPlacementExtent().GetBox().GetExtent();
	const FVector LocalPosition = InversedTransform.TransformPosition(HitLocation);

	//if (LocalCorner.X < MinBounds.X || LocalCorner.X > MaxBounds.X ||
	//	LocalCorner.Y < MinBounds.Y || LocalCorner.Y > MaxBounds.Y ||
	//	LocalCorner.Z < MinBounds.Z || LocalCorner.Z > MaxBounds.Z)

}

void APortalPlatform::SpawnPortal(const bool& CanEnter, AActor*& InPortal, const FVector& HitLocation, const FVector& HitNormal, const FVector& CamRightVector)
{
	if (!CanEnter)
		return;
	
	FVector PortalUp = FVector::CrossProduct(CamRightVector, HitNormal).GetSafeNormal();
	FVector PortalRight = FVector::CrossProduct(HitNormal, PortalUp).GetSafeNormal();
	static FVector2D PortalExtent = FVector2D(Portal->GetComponentByClass<UStaticMeshComponent>()->GetPlacementExtent().GetBox().GetExtent());

	FVector LocalHitLocation = InversedTransform.TransformPosition(HitLocation);
	FVector LocalHitNormal = InversedTransform.TransformVectorNoScale(HitNormal);
	FVector2D AdjustPoint, FaceSize, HitPoint, ValidRange;
	{
		if (FMath::Abs(LocalHitNormal.X) > 0.9f)
		{
			FaceSize = { LocalBoxExtent.Y, LocalBoxExtent.Z };
			HitPoint = { LocalHitLocation.Y, LocalHitLocation.Z };
			ValidRange = FaceSize - FVector2D(PortalExtent.X + EdgeMargin, PortalExtent.Y + EdgeMargin);
			AdjustPoint = FVector2D(FMath::Clamp(HitPoint.X, -ValidRange.X, ValidRange.X), FMath::Clamp(HitPoint.Y, -ValidRange.Y, ValidRange.Y));
		}
		else if (FMath::Abs(LocalHitNormal.Y) > 0.9f)
		{
			FaceSize = { LocalBoxExtent.X, LocalBoxExtent.Z };
			HitPoint = { LocalHitLocation.X, LocalHitLocation.Z };
			ValidRange = FaceSize - FVector2D(PortalExtent.X + EdgeMargin, PortalExtent.Y + EdgeMargin);
			AdjustPoint = FVector2D(FMath::Clamp(HitPoint.X, -ValidRange.X, ValidRange.X), FMath::Clamp(HitPoint.Y, -ValidRange.Y, ValidRange.Y));
		}
		else
		{
			FaceSize = { LocalBoxExtent.X, LocalBoxExtent.Y };
			HitPoint = { LocalHitLocation.X, LocalHitLocation.Y };
			ValidRange = FaceSize - FVector2D(PortalExtent.X + EdgeMargin, PortalExtent.Y + EdgeMargin);
			AdjustPoint = FVector2D(FMath::Clamp(HitPoint.X, -ValidRange.X, ValidRange.X), FMath::Clamp(HitPoint.Y, -ValidRange.Y, ValidRange.Y));
		}
	}
	if (ValidRange.X < 0.f || ValidRange.Y < 0.f)
	{
		return;
	}

	bool bCanPortalDirectly = true;
	TArray<FVector> PortalVertices = {
		HitLocation + PortalRight * PortalExtent.X + PortalUp * PortalExtent.Y,
		HitLocation - PortalRight * PortalExtent.X + PortalUp * PortalExtent.Y,
		HitLocation + PortalRight * PortalExtent.X - PortalUp * PortalExtent.Y,
		HitLocation - PortalRight * PortalExtent.X - PortalUp * PortalExtent.Y
	};
	for (const FVector& Vertex : PortalVertices)
	{
		FVector LocalVertex = InversedTransform.TransformPosition(Vertex);
        
		if (!FBox(-LocalBoxExtent + EdgeMargin, LocalBoxExtent - EdgeMargin).IsInside(LocalVertex))
		{
			bCanPortalDirectly = false;
		}
	}
	
	FRotator NewRotator = FMatrix(PortalUp, PortalRight, HitNormal, FVector::ZeroVector).Rotator();
	if (bCanPortalDirectly && AdjustPoint.Equals(HitPoint, 1.f))
	{
		
		if (InPortal)
		{
			InPortal->SetActorLocationAndRotation(HitLocation, NewRotator);
		}
		return;
	}

	// Pull inside
	FVector NewLocalLocation = LocalHitNormal * (LocalHitNormal.X * LocalBoxExtent.X + LocalHitNormal.Y * LocalBoxExtent.Y + LocalHitNormal.Z * LocalBoxExtent.Z);
	if (FMath::Abs(LocalHitNormal.X) > 0.9f) { NewLocalLocation.Y = AdjustPoint.X; NewLocalLocation.Z = AdjustPoint.Y; }
	else if (FMath::Abs(LocalHitNormal.Y) > 0.9f) { NewLocalLocation.X = AdjustPoint.X; NewLocalLocation.Z = AdjustPoint.Y; }
	else { NewLocalLocation.X = AdjustPoint.X; NewLocalLocation.Y = AdjustPoint.Y; }

	FVector NewWorldLocation = GetActorTransform().TransformPosition(NewLocalLocation);
	if (InPortal)
	{
		InPortal->SetActorLocationAndRotation(NewWorldLocation, NewRotator);
		return;
	}
	
	
}

#pragma region Tiling
void APortalPlatform::UpdateTilingAndScale()
{
	FVector NewScale = FVector(
		TileCount.X * TileWorldSize.X / LocalBoxExtent.X * 2,
		TileCount.Y * TileWorldSize.Y / LocalBoxExtent.Y * 2,
		TileCount.Z * TileWorldSize.Z / LocalBoxExtent.Z * 2
	);
	DEBUG_HELPER_LOG("Local Bound Extents : " + LocalBoxExtent.ToString());

	SetActorScale3D(NewScale);
	CurrentWorldScale = NewScale;

	UpdateMaterialTiling();

	DEBUG_HELPER_LOG("Tile Count : " + TileCount.ToString());
}

void APortalPlatform::SetTileCountX(int32 NewCount)
{
	TileCount.X = NewCount;
	UpdateTilingAndScale();
}

void APortalPlatform::SetTileCountY(int32 NewCount)
{
	TileCount.Y = NewCount;
	UpdateTilingAndScale();
}

void APortalPlatform::SetTileCountZ(int32 NewCount)
{
	TileCount.Z = NewCount;
	UpdateTilingAndScale();
}

TObjectPtr<UMaterialInstanceDynamic> APortalPlatform::GetDynamicMaterial()
{
	if (MeshComp == nullptr || !MeshComp->IsValidLowLevelFast() || MeshComp->GetStaticMesh() == nullptr)
	{
		DEBUG_HELPER_WARNING_THIS_LINE;
		return nullptr;
	}
    
	UMaterialInstanceDynamic* DynamicMat = Cast<UMaterialInstanceDynamic>(MeshComp->GetMaterial(0));
	if (DynamicMat != nullptr && IsValid(DynamicMat))
	{
		DEBUG_HELPER_WARNING_THIS_LINE;
		return DynamicMat;
	}
	
	if (UMaterialInterface* BaseMaterial = MeshComp->GetMaterial(0))
	{
		DynamicMat = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		MeshComp->SetMaterial(0, DynamicMat);
		return DynamicMat;
	}

	DEBUG_HELPER_WARNING_THIS_LINE;
	return nullptr;
}

void APortalPlatform::UpdateMaterialTiling()
{
	UMaterialInstanceDynamic* DynamicMat = GetDynamicMaterial();
	if (UNLIKELY(DynamicMat == nullptr || !IsValid(DynamicMat)))
	{
		DEBUG_HELPER_WARNING_THIS_LINE;
		return;
	}
	
	const float TileU = static_cast<float>(TileCount.X);
	const float TileV = static_cast<float>(TileCount.Y);

	DynamicMat->SetScalarParameterValue(TilingParameterNameU, TileU);
	DynamicMat->SetScalarParameterValue(TilingParameterNameV, TileV);

	CurrentTilingValues = FVector2D(TileU, TileV);
}

#if WITH_EDITOR
void APortalPlatform::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (const FProperty* ChangedProperty = PropertyChangedEvent.Property)
	{
		if (const FName PropertyName = ChangedProperty->GetFName();
			PropertyName == GET_MEMBER_NAME_CHECKED(APortalPlatform, TileCount) ||
			PropertyName == GET_MEMBER_NAME_CHECKED(APortalPlatform, TileWorldSize) ||
			PropertyName == GET_MEMBER_NAME_CHECKED(APortalPlatform, TilingParameterNameU) ||
			PropertyName == GET_MEMBER_NAME_CHECKED(APortalPlatform, TilingParameterNameV)
		)
		{
			UpdateTilingAndScale();
		}
	}
}
#endif WITH_EDITOR
#pragma endregion Tiling

