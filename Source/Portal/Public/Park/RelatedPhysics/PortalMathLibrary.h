// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PortalMathLibrary.generated.h"

/**
 * 
 */


UCLASS()
class PORTAL_API UPortalMathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
#pragma region OPTIMIZATIONS
	static float FusedMultiplyAdd(float MultiplyForward, float MultiplyBackward, float AddLast);

#pragma endregion OPTIMIZATIONS
	
#pragma region DOT
	static float FastDot(const FVector& Origin, const FVector& Target);
	
	static float Gravity(const UWorld* const World, const FVector& Velocity);
	static float LaunchAngle(const UWorld* const World, const FVector& StartPos, const FVector& TargetPos, float LaunchSpeed);
	

#pragma endregion DOT
	
};
