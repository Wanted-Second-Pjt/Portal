// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PortalComponent.generated.h"

class UCameraComponent;
class APortalPlatform;
class APortalPortal;
class UInGameWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTAL_API UPortalComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPortalComponent();

	UFUNCTION(BlueprintCallable, Category="Check")
	bool GetHitResultFromPlatform(const FVector& StartPos, const FVector& Direction, float TraceDistance = 5000.f);
	
	UFUNCTION(BlueprintCallable, Category="Enter")
	FORCEINLINE void SetPortalWeak(AActor* InPortal) { this->WeakPortal = InPortal; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetOrangePortal(APortalPortal* InPortal) { this->OrangePortal = InPortal; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetBluePortal(APortalPortal* InPortal) { this->BluePortal = InPortal; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetAimWidget(UInGameWidget* InGameWidget) { AimWidget = InGameWidget; }

protected:
	// Called when the game starts

	virtual void BeginPlay() override;


protected:
	FCollisionQueryParams Params;

	UPROPERTY(EditAnywhere)
	UInGameWidget* AimWidget;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasPortalGun = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TWeakObjectPtr<AActor> WeakPortal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<APortalPortal> BluePortal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<APortalPortal> OrangePortal;
};
