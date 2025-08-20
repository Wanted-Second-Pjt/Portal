// Copyright Epic Games, Inc. All Rights Reserved.

#include "Park/RelatedPhysics/PortalGameMode.h"

#include "Park/ActorComponents/ControlComponent.h"
#include "PhysicsEngine/PhysicsSettings.h"

#include "Park/Player/PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

APortalGameMode::APortalGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	
	DefaultPawnClass = PlayerPawnClassFinder.Class;  // APlayerCharacter::StaticClass();
	
	
	
}

void APortalGameMode::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputModeGameOnly;
	GetWorld()->GetFirstPlayerController()->SetInputMode(InputModeGameOnly);
	TObjectPtr<APlayerCharacter> Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetOwner());
	if (Player != nullptr && IsValid(Player))
	{
		Player->GetControlComp()->EnableInput(true);
	}
	
	if (UPhysicsSettings* PhysicsSettings = UPhysicsSettings::Get())
	{
		SetupSourceEnginePhysics(PhysicsSettings);
	}
}

void APortalGameMode::SetupSourceEnginePhysics(UPhysicsSettings*& PhysicsSettings ) const
{
	PhysicsSettings->DefaultGravityZ = GravityScale;
	PhysicsSettings->MaxPhysicsDeltaTime = 0.01f;
	PhysicsSettings->bSubstepping = true;
	PhysicsSettings->MaxSubsteps = 4;
}
