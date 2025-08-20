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

	UFUNCTION()
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void SetupSourceEnginePhysics(class UPhysicsSettings*& PhysicsSettings) const;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category = Physics)
	float GravityScale = -1524.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category = Physics)
	float TerminalVelocity = 6667.0f;

	
	

};



