// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/RelatedPhysics/PlayerMovementComponent.h"
#include "PhysicsEngine/PhysicsSettings.h"


UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	GravityScale = 1.0f;
	MaxFlySpeed = TerminalVelocity;
	MaxWalkSpeed = 320.0f;
	JumpZVelocity = 512.0f;
	AirControl = 1.0f;
	FallingLateralFriction = 0.0f;
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UPhysicsSettings* PhysicsSettings = UPhysicsSettings::Get())
	{
		
	}
	
}


void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	if (IsFalling() && Velocity.Z < -TerminalVelocity)
	{
		Velocity.Z = -TerminalVelocity;
	}
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerMovementComponent::ApplyVelocityBraking(float DeltaTime, float Friction, float BrakingDeceleration)
{
	if (IsFalling())
		return;
	
	Super::ApplyVelocityBraking(DeltaTime, Friction, BrakingDeceleration);
}

