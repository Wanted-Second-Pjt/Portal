// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tool.generated.h"

/**
 * 
 */
UCLASS()
class PORTAL_API UTool : public UObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	static FVector ConvertLocationToActorSpace( FVector Location, AActor* Reference, AActor* Target );


	UFUNCTION(BlueprintCallable)
	static FRotator ConvertRotationToActorSpace( FRotator Rotation, AActor* Reference, AActor* Target );

};

