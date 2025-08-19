// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalInstancedStaticMeshActor.generated.h"

UCLASS()
class PORTAL_API APortalInstancedStaticMeshActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APortalInstancedStaticMeshActor();

	//virtual void Tick(float DeltaTime) override;

	
	UFUNCTION(BlueprintCallable)
	virtual void DeActivateCollision();

	UFUNCTION(BlueprintCallable)
	virtual void ActivateCollision();

	UFUNCTION(BlueprintCallable)
	virtual void DrawOwnArea();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInstancedStaticMeshComponent> MeshComp;
};
