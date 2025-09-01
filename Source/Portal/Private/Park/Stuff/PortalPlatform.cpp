// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Stuff/PortalPlatform.h"

#include "Kang/PortalPortal.h"
#include "Kismet/GameplayStatics.h"
//#include "Utility/DebugHelper.h"

TObjectPtr<APortalPlatform> APortalPlatform::OrangePlatform = nullptr;
TObjectPtr<APortalPlatform> APortalPlatform::BluePlatform = nullptr;
TObjectPtr<UStaticMeshComponent> APortalPlatform::PortalMeshComp = nullptr;
TSubclassOf<APortalPortal> APortalPlatform::PortalClass = nullptr;
const float APortalPlatform::EdgeMargin = 10.f;
const float APortalPlatform::SurfaceTolerance = 0.9f;

// Sets default values
APortalPlatform::APortalPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetMobility(EComponentMobility::Static);
	SetRootComponent(MeshComp);
	static ConstructorHelpers::FClassFinder<APortalPortal> Finder(TEXT("/Script/Engine.Blueprint'/Game/Kang/PortalSystem/BP_Portal1.BP_Portal1_C'"));
	if (Finder.Succeeded())
	{
		PortalClass = Finder.Class;
	}
}

void APortalPlatform::BeginPlay()
{
	OrangePlatform = nullptr;
	BluePlatform = nullptr;
	PortalMeshComp = nullptr;
	Super::BeginPlay();
	
	APortalPortal* Portal = Cast<APortalPortal>(UGameplayStatics::GetActorOfClass(GetWorld(), PortalClass));

	TArray<UStaticMeshComponent*> PortalMeshComps;
	Portal->GetComponents<UStaticMeshComponent>(PortalMeshComps, true);
	for (UStaticMeshComponent* PMC : PortalMeshComps)
	{
		if (PMC->GetName() == "PortalPlane")
		{
			PortalMeshComp = PMC;
			break;
		}
	}
	InversedTransform = GetTransform().Inverse();
	if (IsValid(MeshComp->GetStaticMesh()))
	{
		LocalBoxExtent = MeshComp->GetStaticMesh()->GetBoundingBox().GetExtent();
	}

}

void APortalPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

#pragma region Place
bool APortalPlatform::CanPlacePortal(const FVector& HitLocation, const FVector& HitNormal)
{	
	static FVector PortalExtent = InversedTransform.InverseTransformVector(PortalMeshComp->GetPlacementExtent().GetBox().GetExtent());
	
	float MaxPortalDimension = FMath::Max(PortalExtent.X, PortalExtent.Y, PortalExtent.Z);
	FVector LocalNormal = GetActorTransform().InverseTransformVectorNoScale(HitNormal);

	float MinFaceDimension;
	if (FMath::Abs(LocalNormal.X) > 0.9f)
	{
	   MinFaceDimension = FMath::Min(LocalBoxExtent.Y, LocalBoxExtent.Z);
	}
	else if (FMath::Abs(LocalNormal.Y) > 0.9f)
	{
	   MinFaceDimension = FMath::Min(LocalBoxExtent.X, LocalBoxExtent.Z);
	}
	else
	{
	   MinFaceDimension = FMath::Min(LocalBoxExtent.X, LocalBoxExtent.Y);
	}
	//DEBUG_HELPER_PRINT_BOOL(MaxPortalDimension + (EdgeMargin * 2) >= MinFaceDimension);
	return MaxPortalDimension + (EdgeMargin * 2) >= MinFaceDimension;
}

void APortalPlatform::SpawnPortal(const bool& CanEnter, APortalPortal* InPortal, const FVector& HitLocation, const FVector& HitNormal, const FVector& CamRightVector)
{
	if (!CanEnter || !InPortal)
		return;
	
	FVector PortalUp = FVector::CrossProduct(HitNormal, CamRightVector);
	FVector PortalRight = FVector::CrossProduct(HitNormal, PortalUp);
	FRotator NRotator = FMatrix(HitNormal, PortalRight, PortalUp, FVector::ZeroVector).Rotator();
	InPortal->SetActorRotation(NRotator);
	InPortal->SetActorRelativeRotation(NRotator);
	InPortal->SetActorLocation(HitLocation + HitNormal * 5.f);
	
	AddToPlayerInteractionDelegate(InPortal);

	
	//return;
	
	FVector PortalExtent = InPortal->GetComponentByClass<UStaticMeshComponent>()->GetPlacementExtent().GetBox().GetExtent();
	FVector2D LocalPortalExtent = FVector2D(InversedTransform.InverseTransformVector(PortalExtent));

	FVector LocalHitLocation = InversedTransform.TransformPosition(HitLocation);
	FVector LocalHitNormal = InversedTransform.TransformVectorNoScale(HitNormal);
	FVector2D AdjustPoint, FaceSize, HitPoint, ValidRange;
	{
		if (FMath::Abs(LocalHitNormal.X) > 0.9f)
		{
			FaceSize = { LocalBoxExtent.Y, LocalBoxExtent.Z };
			HitPoint = { LocalHitLocation.Y, LocalHitLocation.Z };
			ValidRange = FaceSize - FVector2D(LocalPortalExtent.X + EdgeMargin, LocalPortalExtent.Y + EdgeMargin);
			AdjustPoint = FVector2D(FMath::Clamp(HitPoint.X, -ValidRange.X, ValidRange.X), FMath::Clamp(HitPoint.Y, -ValidRange.Y, ValidRange.Y));
		}
		else if (FMath::Abs(LocalHitNormal.Y) > 0.9f)
		{
			FaceSize = { LocalBoxExtent.X, LocalBoxExtent.Z };
			HitPoint = { LocalHitLocation.X, LocalHitLocation.Z };
			ValidRange = FaceSize - FVector2D(LocalPortalExtent.X + EdgeMargin, LocalPortalExtent.Y + EdgeMargin);
			AdjustPoint = FVector2D(FMath::Clamp(HitPoint.X, -ValidRange.X, ValidRange.X), FMath::Clamp(HitPoint.Y, -ValidRange.Y, ValidRange.Y));
		}
		else
		{
			FaceSize = { LocalBoxExtent.X, LocalBoxExtent.Y };
			HitPoint = { LocalHitLocation.X, LocalHitLocation.Y };
			ValidRange = FaceSize - FVector2D(LocalPortalExtent.X + EdgeMargin, LocalPortalExtent.Y + EdgeMargin);
			AdjustPoint = FVector2D(FMath::Clamp(HitPoint.X, -ValidRange.X, ValidRange.X), FMath::Clamp(HitPoint.Y, -ValidRange.Y, ValidRange.Y));
		}
	}
	//DEBUG_HELPER_PRINT_VECTOR(FVector(ValidRange, 0));
	FRotator NewRotator = FMatrix(HitNormal, PortalRight, PortalUp, FVector::ZeroVector).Rotator();
	if (ValidRange.X > 0.f && ValidRange.Y > 0.f)
	{
		if (InPortal)
		{
			//DEBUG_HELPER_PRINT_LINE();
			InPortal->SetActorLocationAndRotation(HitLocation + HitNormal * 5.f, NewRotator);
		}
		return;
	}

	// Pull inside
	FVector NewLocalLocation;
	if (FMath::Abs(LocalHitNormal.X) > 0.9f)
	{
		NewLocalLocation = FVector(LocalHitNormal.X * LocalBoxExtent.X, AdjustPoint.X, AdjustPoint.Y);
	}
	else if (FMath::Abs(LocalHitNormal.Y) > 0.9f)
	{
		NewLocalLocation = FVector(AdjustPoint.X, LocalHitNormal.Y * LocalBoxExtent.Y,AdjustPoint.Y);
	}
	else if (FMath::Abs(LocalHitNormal.Z) > 0.9f)
	{
		NewLocalLocation = FVector(AdjustPoint.X, AdjustPoint.Y, LocalHitNormal.Z * LocalBoxExtent.Z);
	}
	else
	{
		NewLocalLocation = FVector::ZeroVector;
	}
	FVector NewWorldLocation = GetActorTransform().TransformPosition(NewLocalLocation) + HitNormal * 5.f;
	//DEBUG_HELPER_PRINT_VECTOR(NewWorldLocation);
	
	
	if (InPortal)
	{
		//DEBUG_HELPER_PRINT_INSTANCE();
		InPortal->SetActorLocationAndRotation(NewWorldLocation, NewRotator);
		return;
	}
	
}

void APortalPlatform::AddToPlayerInteractionDelegate(APortalPortal* InPortal)
{
	if (InPortal->ActorHasTag("Blue"))
	{
		//if (IsValid(BluePlatform)) UE_LOG(CustomDebuggingLog, Display, TEXT("%s"), *BluePlatform->GetName());
		if (APortalPlatform::BluePlatform == this)
		{
			return;
		}
		InPortal->OnAttachPortal.RemoveAll(APortalPlatform::BluePlatform);
		InPortal->OnDetachPortal.RemoveAll(APortalPlatform::BluePlatform);
		InPortal->OnAttachPortal.AddDynamic(this, &APortalPlatform::OffPawnCollision);
		InPortal->OnDetachPortal.AddDynamic(this, &APortalPlatform::OnPawnCollision);
		BluePlatform = this;
	}
	else if (InPortal->ActorHasTag("Orange"))
	{
		//if (IsValid(OrangePlatform)) UE_LOG(CustomDebuggingLog, Display, TEXT("%s"), *OrangePlatform->GetName());
		if (APortalPlatform::OrangePlatform == this)
		{
			return;
		}
		InPortal->OnAttachPortal.AddDynamic(this, &APortalPlatform::OffPawnCollision);
		InPortal->OnDetachPortal.AddDynamic(this, &APortalPlatform::OnPawnCollision);
		OrangePlatform = this;
	}
}

void APortalPlatform::OnPawnCollision(APortalPortal* Portal)
{
	//MeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);
	MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
}

void APortalPlatform::OffPawnCollision(APortalPortal* Portal)
{
	//MeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
	MeshComp->SetCollisionResponseToAllChannels(ECR_Overlap);
}

#pragma endregion Place

#pragma region Tiling
void APortalPlatform::UpdateTilingAndScale()
{
	FVector NewScale = FVector(
		TileCount.X * TileWorldSize.X / LocalBoxExtent.X * 2,
		TileCount.Y * TileWorldSize.Y / LocalBoxExtent.Y * 2,
		TileCount.Z * TileWorldSize.Z / LocalBoxExtent.Z * 2
	);
	//DEBUG_HELPER_LOG("Local Bound Extents : " + LocalBoxExtent.ToString());

	SetActorScale3D(NewScale);
	CurrentWorldScale = NewScale;

	UpdateMaterialTiling();

	//DEBUG_HELPER_LOG("Tile Count : " + TileCount.ToString());
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
		//DEBUG_HELPER_WARNING_THIS_LINE;
		return nullptr;
	}
    
	UMaterialInstanceDynamic* DynamicMat = Cast<UMaterialInstanceDynamic>(MeshComp->GetMaterial(0));
	if (DynamicMat != nullptr && IsValid(DynamicMat))
	{
		//DEBUG_HELPER_WARNING_THIS_LINE;
		return DynamicMat;
	}
	
	if (UMaterialInterface* BaseMaterial = MeshComp->GetMaterial(0))
	{
		DynamicMat = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		MeshComp->SetMaterial(0, DynamicMat);
		return DynamicMat;
	}

	//DEBUG_HELPER_WARNING_THIS_LINE;
	return nullptr;
}

void APortalPlatform::UpdateMaterialTiling()
{
	UMaterialInstanceDynamic* DynamicMat = GetDynamicMaterial();
	if (UNLIKELY(DynamicMat == nullptr || !IsValid(DynamicMat)))
	{
		//DEBUG_HELPER_WARNING_THIS_LINE;
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

