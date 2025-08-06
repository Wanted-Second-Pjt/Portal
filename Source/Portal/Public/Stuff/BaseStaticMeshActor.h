// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "BaseStaticMeshActor.generated.h"

UCLASS()
class PORTAL_API ABaseStaticMeshActor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseStaticMeshActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetActorTickEnabled(const bool bEnabled) override;
public:

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
	PURE_VIRTUAL(APortalStaticMeshActor::OnHit, );

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bPortal = true;

};
