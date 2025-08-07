// Copyright Epic Games, Inc. All Rights Reserved.

#include "Park/RelatedPhysics/PortalGameMode.h"

#include "PhysicsEngine/PhysicsSettings.h"

#include "PortalCharacter.h"
#include "UObject/ConstructorHelpers.h"

APortalGameMode::APortalGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

void APortalGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (UPhysicsSettings* PhysicsSettings = UPhysicsSettings::Get())
	{
		SetupSourceEnginePhysics();
	}
}

void APortalGameMode::SetupSourceEnginePhysics() const
{
	UPhysicsSettings* PhysicsSettings = UPhysicsSettings::Get();

	PhysicsSettings->DefaultGravityZ = GravityScale;
	PhysicsSettings->MaxPhysicsDeltaTime = 0.01f;
	PhysicsSettings->bSubstepping = true;
	PhysicsSettings->MaxSubsteps = 4;
}
