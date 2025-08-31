// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Park/Player/PlayerCharacter.h"
#include "PortalPortal.generated.h"

#pragma region Portal_Interaction
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttachPortal, APortalPortal*, InPortal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDetachPortal, APortalPortal*, OutPortal);
#pragma endregion Portal_Interaction

UCLASS(Blueprintable)
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


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneCaptureComponent2D* PortalCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRoot;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInstanceDynamic* PortalMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextureRenderTarget2D* PortalRenderTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APortalPortal* LinkedPortal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LastPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool LastInFront;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentRecursion;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxRecursion = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OffsetValue = -4.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* TeleportObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerCharacter* Player;
	
	
	UFUNCTION(BlueprintNativeEvent)
	void SetClipPlane();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Init();

	UFUNCTION(BlueprintImplementableEvent)
	void Teleport();

	UFUNCTION(BlueprintImplementableEvent)
	void ShouldTeleport();

	UFUNCTION(BlueprintImplementableEvent)
	bool IsPointCrossingPortal(FVector Point, FVector PortalLocation, FVector PortalNormal);

	UFUNCTION(BlueprintImplementableEvent)
	FVector UpdateLocation(FVector OldLocation);

	UFUNCTION(BlueprintImplementableEvent)
	FRotator UpdateRotation(FRotator OldRotation);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSceneCaptureRecursive(FVector Location, FRotator Rotation);

	UFUNCTION(BlueprintImplementableEvent)
	FVector UpdateVelocity(FVector OldVelocity);

	UFUNCTION(BlueprintImplementableEvent)
	void PortalActivation();

	UFUNCTION(BlueprintImplementableEvent)
	void PortalDeactivation();
	
	UFUNCTION()
	void OnPortalNoticeObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOnAttachPortal OnAttachPortal;

	UFUNCTION()
	void OnPortalUnNoticeObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOnDetachPortal OnDetachPortal;
};



