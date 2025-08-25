// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PortalComponent.generated.h"

class UCameraComponent;
class APortalPlatform;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTAL_API UPortalComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPortalComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category="Check")
	bool GetHitResultFromPlatform(const FVector& StartPos, const FVector& EndPos, float TraceDistance = 5000.f);
	
	UFUNCTION(BlueprintCallable, Category="Enter")
	FORCEINLINE void SetPortal(AActor* InPortal) { this->WeakPortal = InPortal; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPortalDefault(AActor* InPortal) { this->Portal = InPortal; }

protected:
	FCollisionQueryParams Params;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TWeakObjectPtr<AActor> WeakPortal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<AActor> Portal;
};
