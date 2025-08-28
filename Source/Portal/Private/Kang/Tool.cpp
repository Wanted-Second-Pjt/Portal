// Fill out your copyright notice in the Description page of Project Settings.


#include "Kang/Tool.h"
 


FVector UTool::ConvertLocationToActorSpace( FVector Location, AActor* Reference, AActor* Target )
{
	if( Reference == nullptr || Target == nullptr )
	{
		return FVector::ZeroVector;
	}

	FVector Direction       = Location - Reference->GetActorLocation();
	FVector TargetLocation  = Target->GetActorLocation();

	FVector Dots;
	Dots.X  = FVector::DotProduct( Direction, Reference->GetActorForwardVector() );
	Dots.Y  = FVector::DotProduct( Direction, Reference->GetActorRightVector() );
	Dots.Z  = FVector::DotProduct( Direction, Reference->GetActorUpVector() );

	FVector NewDirection    = Dots.X * Target->GetActorForwardVector()
							+ Dots.Y * Target->GetActorRightVector()
							+ Dots.Z * Target->GetActorUpVector();

	return TargetLocation + NewDirection;
}


FRotator UTool::ConvertRotationToActorSpace( FRotator Rotation, AActor* Reference, AActor* Target )
{
	if( Reference == nullptr || Target == nullptr )
	{
		return FRotator::ZeroRotator;
	}

	FTransform SourceTransform  = Reference->GetActorTransform();
	FTransform TargetTransform  = Target->GetActorTransform();
	FQuat QuatRotation          = FQuat( Rotation );

	FQuat LocalQuat             = SourceTransform.GetRotation().Inverse() * QuatRotation;
	FQuat NewWorldQuat          = TargetTransform.GetRotation() * LocalQuat;

	return NewWorldQuat.Rotator();
}