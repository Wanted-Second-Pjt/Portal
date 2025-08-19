// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "PortalStaticMeshActor.generated.h"

UCLASS()
class PORTAL_API APortalStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APortalStaticMeshActor();

protected:
	virtual void BeginPlay() override;


public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void LocationUpdate(const FVector& NewLocation)
	{
		SetActorLocation(NewLocation);
	}
	
	UFUNCTION(BlueprintCallable)
	bool Respond(const FHitResult& HitInfo, AActor* Portal);

private:
	void ReadWorldStatus();
	FVector ModifyIfPortalCanMake(const FHitResult& HitInfo, const FVector2D& Extent, float Tolerance = 0.001f) const;
	
public:
	//static FVector PortalExtent;

private:
	float DegreeToPointInForwardSurface = 0.f;
	
	UPROPERTY(EditAnywhere)
	AActor* RefPortal = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	FMatrix FixedInversedRotationScaleMatrix = FMatrix(ForceInitToZero);

	UPROPERTY(EditDefaultsOnly)
	FMatrix FixedInversedScaleMatrix = FMatrix(ForceInitToZero);

};
