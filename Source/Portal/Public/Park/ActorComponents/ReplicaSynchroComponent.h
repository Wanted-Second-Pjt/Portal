// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class AReplicaCharacter;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ReplicaSynchroComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTAL_API UReplicaSynchroComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UReplicaSynchroComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

#pragma region Replica
	UFUNCTION(BlueprintCallable, Category = "Replica")
	void CreateReplica();
	
	UFUNCTION(BlueprintCallable, Category = "Replica")
	void DestroyReplica();
	
	UFUNCTION(BlueprintPure, Category = "Replica")
	AReplicaCharacter* GetCurrentReplica() const { return CurrentReplica; }

	UFUNCTION(BlueprintCallable, Category = "Portal")
	void OnReplicaVisible();
	
	UFUNCTION(BlueprintCallable, Category = "Portal") 
	void OnReplicaInvisible();

protected:
	
	// Sync with Anim Instance Or Pose Data
	UFUNCTION(BlueprintCallable, Category = "Replica")
	void SyncToReplica(const bool& bLink);
	
	// Sync with Pose Data
	UFUNCTION(BlueprintCallable, Category = "Replica")
	void SyncToReplicaPose(const bool& bLink);

	UFUNCTION(BlueprintCallable, Category = "Portal")
	void SetupPortalCamera();
	
#pragma endregion Replica
	
private:
#pragma region Synchro
	void SyncMovementData();
#pragma endregion Synchro

#pragma region Util
	class APlayerCharacter* GetPlayerCharacter() const;
#pragma endregion Util
	
private:
#pragma region Replica
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replica Settings", meta = (AllowPrivateAccess))
	FVector ReplicaSpawnOffset = FVector(100.f, 100.f, 100.f); // Debug : with player
	
	UPROPERTY(BlueprintReadOnly, Category = "Replica", meta = (AllowPrivateAccess))
	TObjectPtr<AReplicaCharacter> CurrentReplica;
#pragma endregion Replica
	
#pragma region Synchro
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synchronization", meta = (AllowPrivateAccess))
	float SyncFrequency = 30.0f; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synchronization", meta = (AllowPrivateAccess))
	bool bSyncMovementState;
	
	float LastSyncTime;
#pragma endregion Synchro
	
	UPROPERTY()
	TObjectPtr<class UPlayerMovementComponent> MovementComp;
	
	UPROPERTY()
	TObjectPtr<class UControlComponent> ControlComp;
	
	UPROPERTY()
	TObjectPtr<class UEquipmentComponent> EquipmentComp;

public:
	
};
