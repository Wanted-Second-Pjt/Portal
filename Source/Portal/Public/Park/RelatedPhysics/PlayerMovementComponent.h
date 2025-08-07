// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTAL_API UPlayerMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UPlayerMovementComponent();

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void ApplyVelocityBraking(float DeltaTime, float Friction, float BrakingDeceleration) override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Physics")
	float TerminalVelocity = 6667.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Physics")
	float PortalTransitionDamping = 0.95f;

	

	
};
