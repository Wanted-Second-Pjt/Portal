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
	// Sets default values for this actor's properties
	APortalPlatform();

	//virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool CanPlacePortal(const FVector& HitLocation, const FVector& SurfaceNormal);

	UFUNCTION(BlueprintCallable)
	void SetEntrance(const bool& CanEnter) const;
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ReadInversedSRTMatrix();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> MeshComp;


protected:
	static UStaticMeshComponent* PortalMesh;
	static const float SurfaceTolerance;

	UPROPERTY(EditDefaultsOnly)
	FMatrix FixedInversedRotationScaleMatrix = FMatrix(ForceInitToZero);

	UPROPERTY(EditDefaultsOnly)
	FMatrix FixedInversedRotationMatrix = FMatrix(ForceInitToZero);
};
