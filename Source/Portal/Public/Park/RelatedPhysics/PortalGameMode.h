// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PortalGameMode.generated.h"

UCLASS(minimalapi)
class APortalGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APortalGameMode();
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Toggle Pause only which Game is Paused 
	UFUNCTION(BlueprintCallable, Category = "Pause")
	void Resume();

protected:
	void TogglePause();

private:
	UFUNCTION()
	void SetupSourceEnginePhysics(class UPhysicsSettings*& PhysicsSettings) const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category = Physics)
	float GravityScale = -1524.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category = Physics)
	float TerminalVelocity = 6667.0f;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class APlayerCharacter> Player;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category = Pause)
	bool bPaused = true;  // first toggle in BeginPlay 
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget), Category = Pause)
	TObjectPtr<class UPortalPauseWidget> PauseMenuWidget;
};



