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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void Respond(const FHitResult& HitInfo, AActor* Portal);

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<AActor> RefPortal = nullptr;
};
