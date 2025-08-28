// Copyright Epic Games, Inc. All Rights Reserved.

#include "Park/RelatedPhysics/PortalGameMode.h"

#include "Park/ActorComponents/ControlComponent.h"
#include "PhysicsEngine/PhysicsSettings.h"

#include "Park/Player/PlayerCharacter.h"
#include "Kang/PortalGameInstance.h"
#include "Kang/PortalPauseWidget.h"
#include "Park/Widget/InGameHUD.h"


APortalGameMode::APortalGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Park/Character/BP_Player"));
	if (PlayerPawnClassFinder.Succeeded())
	{
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	}

	HUDClass = AInGameHUD::StaticClass();
	//DefaultPawnClass = APlayerCharacter::StaticClass();  
	
}

void APortalGameMode::BeginPlay()
{
	Super::BeginPlay();	
	
	if (UPhysicsSettings* PhysicsSettings = UPhysicsSettings::Get())
	{
		SetupSourceEnginePhysics(PhysicsSettings);
	}
	
	if (static IConsoleVariable* LumenGI = IConsoleManager::Get().FindConsoleVariable(TEXT("r.Lumen.DiffuseIndirect.Allow")))
	{
		LumenGI->Set(0);
	}
	
	if (static IConsoleVariable* LumenReflections = IConsoleManager::Get().FindConsoleVariable(TEXT("r.Lumen.Reflections.Allow")))
	{
		LumenReflections->Set(0);
	}
}

void APortalGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(PauseMenuWidget))
	{
		PauseMenuWidget->RemoveFromParent();
	}
	
	Super::EndPlay(EndPlayReason);
}

void APortalGameMode::Resume()
{
	if (bPaused)
	{
		TogglePause();
	}
}

void APortalGameMode::TogglePause()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		LIKELY(IsValid(PlayerController))
	)
	{
		if (UNLIKELY(PauseMenuWidget == nullptr || !IsValid(PauseMenuWidget)))
		{
			PauseMenuWidget = CreateWidget<UPortalPauseWidget>(PlayerController, UPortalPauseWidget::StaticClass());
		}
		
		bPaused = !bPaused;

		PlayerController->SetPause(bPaused);
		PlayerController->SetShowMouseCursor(bPaused);
		bPaused ? PlayerController->SetInputMode(FInputModeUIOnly())
			: PlayerController->SetInputMode(FInputModeGameOnly());
		Player->GetControlComp()->SetEnableInput(!bPaused);
		if (IsValid(PauseMenuWidget))
		{
			bPaused ? PauseMenuWidget->AddToViewport() : PauseMenuWidget->RemoveFromParent();
		}
	}
	else
	{
		UE_LOG(LogGameMode, Warning, TEXT("Player Controller is Not Valid"));
	}
}

void APortalGameMode::SetupSourceEnginePhysics(UPhysicsSettings*& PhysicsSettings ) const
{
	PhysicsSettings->DefaultGravityZ = GravityScale;
	PhysicsSettings->MaxPhysicsDeltaTime = 0.01f;
	PhysicsSettings->bSubstepping = true;
	PhysicsSettings->MaxSubsteps = 4;
}
