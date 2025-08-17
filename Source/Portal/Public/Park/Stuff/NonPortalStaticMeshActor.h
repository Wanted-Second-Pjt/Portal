// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStaticMeshActor.h"
#include "NonPortalStaticMeshActor.generated.h"

UCLASS()
class PORTAL_API ANonPortalStaticMeshActor : public ABaseStaticMeshActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANonPortalStaticMeshActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
};
