// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ReplicaAnimInstance.generated.h"

UCLASS()
class PORTAL_API UReplicaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UReplicaAnimInstance();

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
#pragma region Movement
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float MovementSpeed = 0.0f;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float NormalizedSpeed = 0.0f;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector2D MovementDirection = FVector2D::ZeroVector;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsOnGround = true;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsJumping = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsFalling = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float VerticalSpeed = 0.0f;
#pragma endregion

#pragma region Equipment
	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	bool bHasWeapon = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	float WeaponBobIntensity = 0.0f;
#pragma endregion
	
public:
	UFUNCTION(BlueprintCallable, Category = "Animation Update")
	void UpdateAnimationData(float InMovementSpeed, float InNormalizedSpeed, const FVector2D& InMovementDirection,
		bool InIsOnGround, bool InIsJumping, bool InIsFalling, float InVerticalSpeed,
		bool InHasWeapon, float InWeaponBobIntensity);

private:
	UPROPERTY()
	TObjectPtr<class AReplicaCharacter> OwningReplicaCharacter;
};
