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

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void AddCustomInputVector(FVector WorldVector);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Jump();

	UFUNCTION(BlueprintPure, Category = "Movement")
	bool IsOnGround() const { return bIsOnGround; }

	UFUNCTION(BlueprintPure, Category = "Movement")
	FVector GetCurrentVelocity() const { return Velocity; }


private:
	void ApplyGravity(float DeltaTime);
	
	void ProcessMovement(float DeltaTime); // 버니홉 지원... 뺄까?
	
	void CheckGroundCollision();
	
	bool SweepCollision(const FVector& Start, const FVector& End, FHitResult& HitResult);

	FVector CalculateAirMovement(const FVector& InputVector, float DeltaTime);
	
	//Accel.. or.. hmm...
	FVector CalculateGroundMovement(const FVector& InputVector, float DeltaTime);
	
	
	bool TryStepUp(const FHitResult& Hit, const FVector& Delta);
	
	void HandleSlope(const FVector& SlopeNormal, float DeltaTime);
	
	void ImprovedGroundDetection();

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess), Category = "Portal Physics")
	float TerminalVelocity = 1500.0f;

	// if gravity is not exist in GM. default value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Portal Physics")
	float GravityForce = 800.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Portal Movement")
	float MaxWalkSpeed = 320.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Portal Movement") 
	float MaxAirSpeed = 30.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Portal Movement")
	float JumpVelocity = 270.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Portal Movement")
	float Acceleration = 10.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Portal Movement")
	float Friction = 4.0f; // 마찰력
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Portal Movement")
	float AirAcceleration = 10.0f; // 버니홉 된다는데..
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Portal Terrain")
	float MaxStepHeight = 35.0f; // replace to bone(ex.knee) Height
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Portal Terrain")
	float SlopeLimit = 0.7f; // 0.7f == cos(45degree)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Portal Terrain")
	float SlopeFriction = 2.0f; // 경사면 마찰략
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess), Category = "Physics")
	float PortalTransitionDamping = 0.95f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Physics")
	float GravityScale;
	
private:
	FVector PendingInputVector; // This Frame
	bool bIsOnGround; 
	bool bJumpPressed;
	float GroundCheckDistance = 5.f;
	FVector LastGroundNormal;
	
	bool bOnSlope; 
	FVector CurrentSlopeNormal; 
	float LastStepUpTime; // prevent Spam? search it


};
