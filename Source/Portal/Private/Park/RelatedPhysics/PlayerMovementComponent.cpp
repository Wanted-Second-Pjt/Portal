// Fill out your copyright notice in the Description page of Project Settings.

#include "Park/RelatedPhysics/PlayerMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "Utility/DebugHelper.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"

UPlayerMovementComponent::UPlayerMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	GravityScale = 1.0f; // --> use GameMode Gravity
	
	bIsOnGround = false;
	bJumpPressed = false;
	PendingInputVector = FVector::ZeroVector;
	LastGroundNormal = FVector::UpVector;
	
	bOnSlope = false;
	CurrentSlopeNormal = FVector::UpVector;
	LastStepUpTime = 0.0f;
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	if (!UpdatedComponent || !GetOwner())
	{
		return;
	}
	
	ProcessMovement(DeltaTime);
	
	ApplyGravity(DeltaTime);
	
	if (Velocity.Z < -TerminalVelocity)
	{
		Velocity.Z = -TerminalVelocity;
	}
	
	if (!Velocity.IsNearlyZero())
	{
		FHitResult Hit;
		FVector Delta = Velocity * DeltaTime;
		
		SafeMoveUpdatedComponent(Delta, UpdatedComponent->GetComponentRotation(), true, Hit);

		// interact stairs
		if (Hit.bBlockingHit)
		{
			float CurrentTime = GetWorld()->GetTimeSeconds();
			if (CurrentTime - LastStepUpTime > 0.1f && TryStepUp(Hit, Delta))
			{
				LastStepUpTime = CurrentTime;
			}
			else
			{
				// wall sliding
				SlideAlongSurface(Delta, 1.0f - Hit.Time, Hit.Normal, Hit);
			}
		}
	}
	
	ImprovedGroundDetection();
	
	if (bOnSlope && bIsOnGround)
	{
		HandleSlope(CurrentSlopeNormal, DeltaTime);
	}
	
	PendingInputVector = FVector::ZeroVector;
	bJumpPressed = false;
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerMovementComponent::AddCustomInputVector(FVector WorldVector)
{
	PendingInputVector += WorldVector;
}

void UPlayerMovementComponent::Jump()
{
	if (bIsOnGround)
	{
		bJumpPressed = true;
	}
}

void UPlayerMovementComponent::ApplyGravity(float DeltaTime)
{
	if (!bIsOnGround)
	{
		// gamemode gravity
		if (UPhysicsSettings* PhysicsSettings = UPhysicsSettings::Get())
		{
			float WorldGravity = PhysicsSettings->DefaultGravityZ * GravityScale;
			Velocity.Z += WorldGravity * DeltaTime;
		}
		else
		{
			
			Velocity.Z -= GravityForce * GravityScale * DeltaTime;
		}
	}
}

void UPlayerMovementComponent::ProcessMovement(float DeltaTime)
{
	if (PendingInputVector.IsNearlyZero() && !bJumpPressed)
	{
		if (bIsOnGround)
		{
			FVector HorizontalVelocity = FVector(Velocity.X, Velocity.Y, 0);
			HorizontalVelocity = HorizontalVelocity * FMath::Max(0.0f, 1.0f - Friction * DeltaTime);
			Velocity.X = HorizontalVelocity.X;
			Velocity.Y = HorizontalVelocity.Y;
		}
		return;
	}
	
	if (bJumpPressed && bIsOnGround)
	{
		Velocity.Z = JumpVelocity;
		bIsOnGround = false;
	}

	FVector HorizontalInput = PendingInputVector;
	HorizontalInput.Z = 0;
	
	if (!HorizontalInput.IsNearlyZero())
	{
		HorizontalInput.Normalize();
		
		if (bIsOnGround)
		{
			FVector NewVelocity = CalculateGroundMovement(HorizontalInput, DeltaTime);
			Velocity.X = NewVelocity.X;
			Velocity.Y = NewVelocity.Y;
		}
		else
		{
			FVector AirMovement = CalculateAirMovement(HorizontalInput, DeltaTime);
			Velocity.X += AirMovement.X;
			Velocity.Y += AirMovement.Y;
		}
	}
}

FVector UPlayerMovementComponent::CalculateGroundMovement(const FVector& InputVector, float DeltaTime)
{
	FVector CurrentHorizontalVelocity = FVector(Velocity.X, Velocity.Y, 0);
	FVector TargetVelocity = InputVector * MaxWalkSpeed;
	
	// Accel
	FVector VelocityDiff = TargetVelocity - CurrentHorizontalVelocity;
	float AddSpeed = VelocityDiff.Size();
	
	if (AddSpeed > 0)
	{
		float AccelSpeed = Acceleration * DeltaTime * MaxWalkSpeed;
		if (AccelSpeed > AddSpeed)
		{
			AccelSpeed = AddSpeed;
		}
		
		VelocityDiff.Normalize();
		return CurrentHorizontalVelocity + VelocityDiff * AccelSpeed;
	}
	
	return CurrentHorizontalVelocity;
}

FVector UPlayerMovementComponent::CalculateAirMovement(const FVector& InputVector, float DeltaTime)
{
	FVector CurrentHorizontalVelocity = FVector(Velocity.X, Velocity.Y, 0);
	float CurrentSpeed = CurrentHorizontalVelocity.Size();
	
	FVector CurrentDir = CurrentSpeed > 0 ? CurrentHorizontalVelocity / CurrentSpeed : FVector::ZeroVector;
	
	float Dot = FVector::DotProduct(CurrentDir, InputVector);
	float AddSpeed = MaxAirSpeed - CurrentSpeed * Dot;
	
	if (AddSpeed > 0)
	{
		float AccelSpeed = AirAcceleration * DeltaTime * MaxAirSpeed;
		if (AccelSpeed > AddSpeed)
		{
			AccelSpeed = AddSpeed;
		}
		
		return InputVector * AccelSpeed;
	}
	
	return FVector::ZeroVector;
}

void UPlayerMovementComponent::CheckGroundCollision()
{
	if (!UpdatedComponent)
	{
		return;
	}

	FVector Start = UpdatedComponent->GetComponentLocation();
	FVector End = Start - FVector(0, 0, GroundCheckDistance);
	
	FHitResult Hit;
	if (SweepCollision(Start, End, Hit))
	{
		if (Hit.Normal.Z > SlopeLimit)
		{
			if (!bIsOnGround && Velocity.Z <= 0)
			{
				bIsOnGround = true;
				LastGroundNormal = Hit.Normal;
				
				// step on ground
				if (Velocity.Z < 0)
				{
					Velocity.Z = 0;
				}
			}
		}
	}
	else
	{
		bIsOnGround = false;
	}
}

bool UPlayerMovementComponent::SweepCollision(const FVector& Start, const FVector& End, FHitResult& HitResult)
{
	if (!UpdatedComponent || !GetWorld())
	{
		return false;
	}

	return GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_WorldStatic,
		GetOwner()->GetComponentByClass<UCapsuleComponent>()->GetCollisionShape()
	);
}

void UPlayerMovementComponent::EnterPortal()
{
	Velocity *= PortalTransitionDamping;
	DEBUG_HELPER_PRINT_LINE();  // check enter portal
}

bool UPlayerMovementComponent::TryStepUp(const FHitResult& Hit, const FVector& Delta)
{
	if (!UpdatedComponent || !GetWorld())
	{
		return false;
	}
	
	FVector UpSweep = FVector(0, 0, MaxStepHeight);
	FVector StartLocation = UpdatedComponent->GetComponentLocation();
	FHitResult UpHit;
	
	if (SweepCollision(StartLocation, StartLocation + UpSweep, UpHit))
	{
		// Prevent by obstacle
		return false;
	}
	
	FVector ForwardSweep = FVector(Delta.X, Delta.Y, 0).GetSafeNormal() * Delta.Size();
	FVector TopLocation = StartLocation + UpSweep;
	FHitResult ForwardHit;
	
	if (SweepCollision(TopLocation, TopLocation + ForwardSweep, ForwardHit))
	{
		// Prevent by obstacle
		return false;
	}
	
	FVector DownSweep = FVector(0, 0, -MaxStepHeight);
	FVector ForwardLocation = TopLocation + ForwardSweep;
	FHitResult DownHit;
	
	if (SweepCollision(ForwardLocation, ForwardLocation + DownSweep, DownHit))
	{
		if (DownHit.Normal.Z > SlopeLimit)
		{
			FVector NewLocation = DownHit.Location + FVector(0, 0, 2.0f); // 약간 위로
			UpdatedComponent->SetWorldLocation(NewLocation);
			
			if (Velocity.Z < 0)
			{
				Velocity.Z = 0;
			}
			
			return true;
		}
	}
	
	return false;
}

void UPlayerMovementComponent::HandleSlope(const FVector& SlopeNormal, float DeltaTime)
{
	if (!bIsOnGround || SlopeNormal.Z > SlopeLimit)
	{
		bOnSlope = false;
		return;
	}
	
	FVector HorizontalVelocity = FVector(Velocity.X, Velocity.Y, 0);
	float SlopeFactor = 1.0f - SlopeNormal.Z; // 경사가 급할수록 큰 값
	float TotalFriction = Friction + (SlopeFriction * SlopeFactor);
	
	HorizontalVelocity = HorizontalVelocity * FMath::Max(0.0f, 1.0f - TotalFriction * DeltaTime);
	Velocity.X = HorizontalVelocity.X;
	Velocity.Y = HorizontalVelocity.Y;
	
	if (SlopeFactor > 0.5f && PendingInputVector.IsNearlyZero())
	{
		FVector SlideDirection = FVector::VectorPlaneProject(FVector(0, 0, -1), SlopeNormal).GetSafeNormal();
		float SlideForce = SlopeFactor * 100.0f;  // Hard Coding
		
		Velocity += SlideDirection * SlideForce * DeltaTime;
	}
}

void UPlayerMovementComponent::ImprovedGroundDetection()
{
	if (!UpdatedComponent)
	{
		return;
	}
	
	FVector StartLocation = UpdatedComponent->GetComponentLocation();
	bool bFoundGround = false;
	FVector BestGroundNormal = FVector::UpVector;
	float ClosestGroundDistance = GroundCheckDistance;
	
	TArray<FVector> CheckDirections = {
		FVector(0, 0, -1),        // 중앙 아래
		FVector(5, 0, -1),        // 앞쪽 아래
		FVector(-5, 0, -1),       // 뒤쪽 아래  
		FVector(0, 5, -1),        // 우측 아래
		FVector(0, -5, -1)        // 좌측 아래
	};
	
	for (const FVector& Direction : CheckDirections)
	{
		FVector EndLocation = StartLocation + Direction.GetSafeNormal() * GroundCheckDistance;
		FHitResult Hit;
		
		if (SweepCollision(StartLocation, EndLocation, Hit))
		{
			float Distance = FVector::Dist(StartLocation, Hit.Location);
			
			// Find Ground can stand on
			if (Distance < ClosestGroundDistance && Hit.Normal.Z > 0.3f)
			{
				bFoundGround = true;
				BestGroundNormal = Hit.Normal;
				ClosestGroundDistance = Distance;
			}
		}
	}
	
	if (bFoundGround)
	{
		if (!bIsOnGround && Velocity.Z <= 0)
		{
			bIsOnGround = true;
			LastGroundNormal = BestGroundNormal;
			
			if (Velocity.Z < 0)
			{
				Velocity.Z = 0;
			}
		}
		
		if (BestGroundNormal.Z < SlopeLimit)
		{
			bOnSlope = true;
			CurrentSlopeNormal = BestGroundNormal;
		}
		else
		{
			bOnSlope = false;
			CurrentSlopeNormal = FVector::UpVector;
		}
	}
	else
	{
		bIsOnGround = false;
		bOnSlope = false;
	}
}
