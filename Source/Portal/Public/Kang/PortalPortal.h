// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PortalPortal.generated.h"

UCLASS()
class PORTAL_API APortalPortal : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	APortalPortal();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Status of the Portal (being visualized by the player or not)
	UFUNCTION(BlueprintPure)
	bool IsActive();

	UFUNCTION(BlueprintCallable)
	void SetActive( bool NewActive );

	//Render target to use to display the portal
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ClearRTT();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetRTT( UTexture* RenderTexture );

	UFUNCTION(BlueprintNativeEvent)
	void ForceTick();

	//Target of where the portal is looking
	UFUNCTION(BlueprintPure)
	AActor* GetTarget();

	UFUNCTION(BlueprintCallable)
	void SetTarget( AActor* NewTarget );

	//Helpers
	UFUNCTION(BlueprintCallable)
	bool IsPointInFrontOfPortal( FVector Point, FVector PortalLocation, FVector PortalNormal );

	UFUNCTION(BlueprintCallable)
	bool IsPointCrossingPortal( FVector Point, FVector PortalLocation, FVector PortalNormal );

	/*UFUNCTION(BlueprintCallable)
	void TeleportActor( AActor* ActorToTeleport );*/
	
protected:
	UPROPERTY(BlueprintReadOnly)
	USceneComponent* PortalRootComponent;

private:
	bool bIsActive;

	AActor* Target;

	//Used for Tracking movement of a point
	FVector LastPosition;
	bool    LastInFront;
};



