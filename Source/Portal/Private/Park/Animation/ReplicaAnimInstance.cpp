// Fill out your copyright notice in the Description page of Project Settings.

#include "Park/Animation/ReplicaAnimInstance.h"
#include "Park/Player/ReplicaCharacter.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

UReplicaAnimInstance::UReplicaAnimInstance()
{
	MovementSpeed = 0.0f;
	NormalizedSpeed = 0.0f;
	MovementDirection = FVector2D::ZeroVector;
	bIsOnGround = true;
	bIsJumping = false;
	bIsFalling = false;
	VerticalSpeed = 0.0f;
	bHasWeapon = false;
	WeaponBobIntensity = 0.0f;
	
	OwningReplicaCharacter = nullptr;
}

void UReplicaAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (!OwningReplicaCharacter)
	{
		OwningReplicaCharacter = Cast<AReplicaCharacter>(GetOwningActor());
	}
	
	if (OwningReplicaCharacter && IsValid(OwningReplicaCharacter))
	{
		const FReplicaAnimationData& AnimData = OwningReplicaCharacter->GetAnimationData();
		
		MovementSpeed = AnimData.MovementSpeed;
		NormalizedSpeed = AnimData.NormalizedSpeed;
		MovementDirection = AnimData.MovementDirection;
		bIsOnGround = AnimData.bIsOnGround;
		bIsJumping = AnimData.bIsJumping;
		bIsFalling = AnimData.bIsFalling;
		VerticalSpeed = AnimData.VerticalSpeed;
		bHasWeapon = AnimData.bHasWeapon;
		WeaponBobIntensity = AnimData.WeaponBobIntensity;
	}
}

void UReplicaAnimInstance::UpdateAnimationData(float InMovementSpeed, float InNormalizedSpeed, 
	const FVector2D& InMovementDirection, bool InIsOnGround, bool InIsJumping, bool InIsFalling, 
	float InVerticalSpeed, bool InHasWeapon, float InWeaponBobIntensity)
{
	MovementSpeed = InMovementSpeed;
	NormalizedSpeed = InNormalizedSpeed;
	MovementDirection = InMovementDirection;
	bIsOnGround = InIsOnGround;
	bIsJumping = InIsJumping;
	bIsFalling = InIsFalling;
	VerticalSpeed = InVerticalSpeed;
	bHasWeapon = InHasWeapon;
	WeaponBobIntensity = InWeaponBobIntensity;
}
