// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalPlatform.generated.h"

UCLASS()
class PORTAL_API APortalPlatform : public AActor
{
	GENERATED_BODY()

public:
	APortalPlatform();

protected:
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

#pragma region PortalPlacement
public:
	UFUNCTION(BlueprintCallable, Category="Portal")
	bool CanPlacePortal(const FVector& HitLocation, const FVector& HitNormal);

	UFUNCTION(BlueprintCallable, Category="Portal")
	void SpawnPortal(const bool& CanEnter, AActor* InPortal, const FVector& HitLocation, const FVector& HitNormal, const FVector& CamRightVector);

protected:
	//void Facing(const FVector& LocalPoint, const FVector& LocalNormal);
#pragma endregion PortalPlacement

#pragma region Tiling
public:
	UFUNCTION(BlueprintCallable, Category = "Material Tiling")
	void UpdateTilingAndScale();

	UFUNCTION(BlueprintCallable, Category = "Material Tiling")
	void SetTileCountX(int32 NewCount);

	UFUNCTION(BlueprintCallable, Category = "Material Tiling")
	void SetTileCountY(int32 NewCount);

	UFUNCTION(BlueprintCallable, Category = "Material Tiling")
	void SetTileCountZ(int32 NewCount);

#if WITH_EDITOR

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION(CallInEditor, Category = "Material Tiling|Quick Actions")
	void IncrementTileX() { TileCount.X++; UpdateTilingAndScale(); }

	UFUNCTION(CallInEditor, Category = "Material Tiling|Quick Actions")
	void DecrementTileX() { TileCount.X -= (TileCount.X > 1 ? 1 : 0); UpdateTilingAndScale(); }

	UFUNCTION(CallInEditor, Category = "Material Tiling|Quick Actions")
	void IncrementTileY() { TileCount.Y++; UpdateTilingAndScale(); }

	UFUNCTION(CallInEditor, Category = "Material Tiling|Quick Actions")
	void DecrementTileY() { TileCount.Y -= (TileCount.Y > 1 ? 1 : 0); UpdateTilingAndScale(); }

	UFUNCTION(CallInEditor, Category = "Material Tiling|Quick Actions")
	void ResetTiling() { TileCount = FIntVector(1, 1, 1); UpdateTilingAndScale(); }

#endif WITH_EDITOR

private:
	TObjectPtr<UMaterialInstanceDynamic> GetDynamicMaterial();
	void UpdateMaterialTiling();
#pragma endregion Tiling
	


#pragma region Component
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> MeshComp;
#pragma endregion Component

#pragma region Tiling
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Tiling", meta = (ClampMin = "1", ClampMax = "100"))
	FIntVector TileCount = FIntVector(1, 1, 1);
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Tiling", meta = (ClampMin = "1.0"))
	FVector TileWorldSize = FVector(100.0f, 100.0f, 100.0f);
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Tiling")
	FName TilingParameterNameU = "TileU";
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material Tiling")
	FName TilingParameterNameV = "TileV";
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Tiling|Info")
	FVector CurrentWorldScale = FVector(1.0f, 1.0f, 1.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Material Tiling|Info")
	FVector2D CurrentTilingValues = FVector2D(1.0f, 1.0f);

	FVector LocalBoxExtent = FVector::ZeroVector;
#pragma endregion Tiling
	
#pragma region PortalPlacement
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Portal")
	FTransform InversedTransform;

private:
	
	static TObjectPtr<AActor> Portal;
	static TSubclassOf<AActor> PortalClass;
	const static float EdgeMargin;
	static const float SurfaceTolerance;
#pragma endregion PortalPlacement

	
};
