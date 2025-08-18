// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStaticMeshActor.h"
#include "PortalStaticMeshActor.generated.h"

UCLASS()
class PORTAL_API APortalStaticMeshActor : public ABaseStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APortalStaticMeshActor();

protected:
	virtual void PostInitializeComponents() override;
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
	

private:
	float DegreeToPointInForwardSurface = 0.f;
	static FVector PortalExtent;
	
	UPROPERTY(EditDefaultsOnly)
	FMatrix FixedInversedRotationScaleMatrix = FMatrix(ForceInitToZero);

	UPROPERTY(EditDefaultsOnly)
	FMatrix FixedInversedScaleMatrix = FMatrix(ForceInitToZero);

};
