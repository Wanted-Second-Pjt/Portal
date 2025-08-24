// Copyright Epic Games, Inc. All Rights Reserved.

#include "Park/RelatedPhysics/PortalGameMode.h"

#include "Park/ActorComponents/ControlComponent.h"
#include "PhysicsEngine/PhysicsSettings.h"

#include "Park/Player/PlayerCharacter.h"
#include "Kang/PortalGameInstance.h"
#include "Kang/PortalPauseWidget.h"


APortalGameMode::APortalGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	
	//DefaultPawnClass = PlayerPawnClassFinder.Class;
	DefaultPawnClass = APlayerCharacter::StaticClass();  
	
}

void APortalGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (TObjectPtr<APlayerController> PlayerController = GetWorld()->GetFirstPlayerController())
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
		Player = Cast<APlayerCharacter>(PlayerController->GetPawn());
		if (IsValid(Player))
		{
			Player->GetControlComp()->EnableInput(true);
		}
		else
		{
			return;
		}
		
	#pragma region Pause
		//bPaused = false;
		//if (!PauseMenuWidget || !IsValid(PauseMenuWidget))
		//{
		//	PauseMenuWidget = CreateWidget<UPortalPauseWidget>(PlayerController, UPortalPauseWidget::StaticClass());
		//}
		//EnableInput(PlayerController);
		//if (UInputComponent* EnabledInputComp = InputComponent)
		//{
		//	EnabledInputComp->BindKey(EKeys::P, IE_Pressed, this, &APortalGameMode::TogglePause);
		//}
	#pragma endregion Pause
	}
	
	if (UPhysicsSettings* PhysicsSettings = UPhysicsSettings::Get())
	{
		SetupSourceEnginePhysics(PhysicsSettings);
	}
	
	if (static IConsoleVariable* LumenGI = IConsoleManager::Get().FindConsoleVariable(TEXT("r.Lumen.DiffuseIndirect.Allow"));)
	{
		LumenGI->Set(0);
	}
	
	if (static IConsoleVariable* LumenReflections = IConsoleManager::Get().FindConsoleVariable(TEXT("r.Lumen.Reflections.Allow"));)
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
		PlayerController->SetInputMode(bPaused ? FInputModeUIOnly() : FInputModeGameOnly());
		Player->GetControlComp()->EnableInput(!bPaused);
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
