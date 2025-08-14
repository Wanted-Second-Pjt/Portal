// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "PlayerMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTAL_API UPlayerMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

public:
	UPlayerMovementComponent();

public:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void EnterPortal(); // Clamping

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Physics")
	float TerminalVelocity = 6667.0f;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Physics")
	float PortalTransitionDamping = 0.95f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Physics")
	float GravityScale;

	/*
public:
	UFUNCTION(BlueprintPure, Category="Pawn|Components|CharacterMovement")
	FVector::FReal GetGravitySpaceZ(const FVector& Vector) const { return Vector.Dot(-GetGravityDirection()); }
	FVector ProjectToGravityFloor(const FVector& Vector) const { return FVector::VectorPlaneProject(Vector, GetGravityDirection()); }
	FVector GetGravityDirection() const { return GravityDirection; }
	
	
	UPROPERTY(Category="Character Movement: Gravity", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FVector GravityDirection;
	
	UPROPERTY(Category="Character Movement: Walking", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0", ForceUnits="cm/s"))
	float MaxWalkSpeed;
	UPROPERTY(Category="Character Movement: Flying", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0", ForceUnits="cm/s"))
	float MaxFlySpeed;
	UPROPERTY(Category="Character Movement: Jumping / Falling", EditAnywhere, BlueprintReadWrite, meta=(DisplayName="Jump Z Velocity", ClampMin="0", UIMin="0", ForceUnits="cm/s"))
	float JumpZVelocity;
	UPROPERTY(Category="Character Movement: Jumping / Falling", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0"))
	float AirControl;
	UPROPERTY(Category="Character Movement: Jumping / Falling", EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0", UIMin="0"))
	float FallingLateralFriction;
	
	UPROPERTY(Category="Character Movement: Physics Interaction", EditAnywhere, BlueprintReadWrite, meta=(editcondition = "bEnablePhysicsInteraction"))
	float StandingDownwardForceScale;

	UPROPERTY(Category="Character Movement (General Settings)", EditAnywhere, BlueprintReadWrite, AdvancedDisplay, meta=(ClampMin="1", ClampMax="25", UIMin="1", UIMax="25"))
	int32 MaxSimulationIterations;
	UPROPERTY(Category="Character Movement (General Settings)", EditAnywhere, BlueprintReadWrite, AdvancedDisplay, meta=(ClampMin="0.0166", ClampMax="0.50", UIMin="0.0166", UIMax="0.50"))
	float MaxSimulationTimeStep;

	ENGINE_API virtual bool CheckFall(const FFindFloorResult& OldFloor, const FHitResult& Hit, const FVector& Delta, const FVector& OldLocation, float remainingTime, float timeTick, int32 Iterations, bool bMustJump);
	bool UCharacterMovementComponent::CheckFall(const FFindFloorResult& OldFloor, const FHitResult& Hit, const FVector& Delta, const FVector& OldLocation, float remainingTime, float timeTick, int32 Iterations, bool bMustJump)
	{
		if (!HasValidData())
		{
			return false;
		}

		if (bMustJump || CanWalkOffLedges())
		{
			HandleWalkingOffLedge(OldFloor.HitResult.ImpactNormal, OldFloor.HitResult.Normal, OldLocation, timeTick);
			if (IsMovingOnGround())
			{
				// If still walking, then fall. If not, assume the user set a different mode they want to keep.
				StartFalling(Iterations, remainingTime, timeTick, Delta, OldLocation);
			}
			return true;
		}
		return false;
	}
	void UCharacterMovementComponent::StartFalling(int32 Iterations, float remainingTime, float timeTick, const FVector& Delta, const FVector& subLoc)
	{
		// start falling 
		const float DesiredDist = Delta.Size();
		const float ActualDist = ProjectToGravityFloor(UpdatedComponent->GetComponentLocation() - subLoc).Size();
		remainingTime = (DesiredDist < UE_KINDA_SMALL_NUMBER)
						? 0.f
						: remainingTime + timeTick * (1.f - FMath::Min(1.f,ActualDist/DesiredDist));

		if ( IsMovingOnGround() )
		{
			// This is to catch cases where the first frame of PIE is executed, and the
			// level is not yet visible. In those cases, the player will fall out of the
			// world... So, don't set MOVE_Falling straight away.
			if ( !GIsEditor || (GetWorld()->HasBegunPlay() && (GetWorld()->GetTimeSeconds() >= 1.f)) )
			{
				SetMovementMode(MOVE_Falling); //default behavior if script didn't change physics
			}
			else
			{
				// Make sure that the floor check code continues processing during this delay.
				bForceNextFloorCheck = true;
			}
		}
		StartNewPhysics(remainingTime,Iterations);
	}
	*/
};
