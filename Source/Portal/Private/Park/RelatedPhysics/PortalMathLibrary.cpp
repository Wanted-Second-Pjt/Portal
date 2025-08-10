// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/RelatedPhysics/PortalMathLibrary.h"

// 따로 처리해야할 곱,더하기 연산자를 한번에 register에 전달시켜 줌. 이미 그렇게 하고있는 cpu도 많다.
float UPortalMathLibrary::FusedMultiplyAdd(float MultiplyForward, float MultiplyBackward, float AddLast)
{
	#if PLATFORM_WINDOWS && PLATFORM_64BITS
		return _mm_cvtss_f32(_mm_fmadd_ss(_mm_set_ss(MultiplyForward), _mm_set_ss(MultiplyBackward), _mm_set_ss(AddLast)));
	#elif (PLATFORM_MAC || PLATFORM_IOS) && defined(__aarch64__)
		return vfams_32(AddLast, MultiplyForward, MultiplyBackward);
	#else
		return MultiplyForward * MultiplyBackward + AddLast;
	#endif
}

float UPortalMathLibrary::FastDot(const FVector& Origin, const FVector& Target)
{
	return 0.f;
}

float UPortalMathLibrary::Gravity(const UWorld* const World, const FVector& Velocity)
{
	return Velocity.Z * World->GetGravityZ();
}

float UPortalMathLibrary::LaunchAngle(const UWorld* const World, const FVector& StartPos, const FVector& TargetPos, float LaunchSpeed)
{
	if (World == nullptr) return -1.0f;
	FVector Delta = TargetPos - StartPos;
	float HorizontalDistance = FVector2D(Delta.X, Delta.Y).Length();
	float VerticalDistance = Delta.Z;

	float SquaredSpeed = LaunchSpeed * LaunchSpeed;
	float Discriminant =
		SquaredSpeed * SquaredSpeed - World->GetGravityZ() * (
			World->GetGravityZ() * HorizontalDistance * HorizontalDistance
			+ 2.0f * VerticalDistance * SquaredSpeed
		);

	if (Discriminant < 0.0f) return 0.1f;
	
	return FMath::Atan((SquaredSpeed - FMath::Sqrt(Discriminant)) / World->GetGravityZ() * HorizontalDistance);
	
	
}
