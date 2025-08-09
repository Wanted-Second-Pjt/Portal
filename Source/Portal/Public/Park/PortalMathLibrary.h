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

	static FVector Normalized(const FVector& Origin);

#pragma region VECTOR
	static float Dot(const FVector& Origin, const FVector& Target);
	static float NormalizedDot(const FVector& Origin, const FVector& Target);

	static FVector Cross(const FVector& Origin, const FVector& Target);
#pragma endregion VECTOR
};
