// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PortalComponent.generated.h"

#pragma region Portal_Interaction
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAttachPortal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDetachPortal);
#pragma endregion Portal_Interaction

class UCameraComponent;
class APortalPlatform;
class UInGameWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTAL_API UPortalComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPortalComponent();

	UFUNCTION(BlueprintCallable, Category="Check")
	bool GetHitResultFromPlatform(const FVector& StartPos, const FVector& EndPos, float TraceDistance = 5000.f);
	
	UFUNCTION(BlueprintCallable, Category="Enter")
	FORCEINLINE void SetPortalWeak(AActor* InPortal) { this->WeakPortal = InPortal; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetOrangePortal(AActor* InPortal) { this->OrangePortal = InPortal; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetBluePortal(AActor* InPortal) { this->BluePortal = InPortal; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetAimWidget(UInGameWidget* InGameWidget) { AimWidget = InGameWidget; }

protected:
	// Called when the game starts

	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Player Portal Events")
	FOnAttachPortal OnAttachPortal;
	
	UPROPERTY(BlueprintAssignable, Category = "Player Portal Events")
	FOnDetachPortal OnDetachPortal;

protected:
	FCollisionQueryParams Params;

	UPROPERTY(EditAnywhere)
	UInGameWidget* AimWidget;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TWeakObjectPtr<AActor> WeakPortal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<AActor> BluePortal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<AActor> OrangePortal;
};
