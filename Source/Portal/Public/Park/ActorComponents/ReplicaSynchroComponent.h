// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "ReplicaSynchroComponent.generated.h"

#pragma region ReplicaSynchro
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReplicaCreated, ACharacter*, Replica);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReplicaDestroyed, ACharacter*, Replica);
#pragma endregion ReplicaSynchro


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
	
	UFUNCTION(BlueprintCallable, Category = "Replica")
	void SyncToReplica();
	
	UFUNCTION(BlueprintPure, Category = "Replica")
	ACharacter* GetCurrentReplica() const { return CurrentReplica; }

	UFUNCTION(BlueprintCallable, Category = "Portal")
	void OnPlayerEnterPortal();
	
	UFUNCTION(BlueprintCallable, Category = "Portal") 
	void OnPlayerExitPortal();
	
	UFUNCTION(BlueprintCallable, Category = "Portal")
	void UpdateReplicaVisibility(bool bVisible);
#pragma endregion Replica
	
private:
#pragma region Synchro
	void SyncBoneTransforms();
	void SyncAnimationState();
	void SyncMovementData();
	void SyncEquipmentState();
	void SyncPortalWeaponAnimation();
#pragma endregion Synchro

#pragma region Util
	class APlayerCharacter* GetPlayerCharacter() const;
	void SetAnimInstanceProperty(const FString& PropertyName, float Value);
	void SetAnimInstanceProperty(const FString& PropertyName, bool Value);
	void SetAnimInstanceProperty(const FString& PropertyName, const FVector2D& Value);
#pragma endregion Util
	
private:
#pragma region Replica
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replica Settings", meta = (AllowPrivateAccess))
	TSubclassOf<ACharacter> ReplicaClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Replica Settings", meta = (AllowPrivateAccess))
	FVector ReplicaSpawnOffset = FVector(0, 100, 0); // Debug : side to player
	
	UPROPERTY(BlueprintReadOnly, Category = "Replica", meta = (AllowPrivateAccess))
	TObjectPtr<ACharacter> CurrentReplica;
#pragma endregion Replica
	
#pragma region Synchro
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synchronization", meta = (AllowPrivateAccess))
	float SyncFrequency = 30.0f; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synchronization", meta = (AllowPrivateAccess))
	bool bSyncBoneTransforms = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synchronization", meta = (AllowPrivateAccess))
	bool bSyncMovementState = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Synchronization", meta = (AllowPrivateAccess))
	bool bSyncEquipmentState = true;
	
	// about fade. delete this
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal Effects", meta = (AllowPrivateAccess))
	float PortalFadeSpeed = 2.0f; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal Effects", meta = (AllowPrivateAccess))
	bool bHideReplicaDuringPortalTransition = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bone Sync", meta = (AllowPrivateAccess))
	TArray<FName> ImportantBones = {
		TEXT("spine_01"), TEXT("spine_02"), TEXT("spine_03"),
		TEXT("head"), TEXT("neck_01"),
		TEXT("upperarm_l"), TEXT("upperarm_r"),
		TEXT("lowerarm_l"), TEXT("lowerarm_r"),
		TEXT("hand_l"), TEXT("hand_r"),
		TEXT("portalgun_r")
	};
	
	float LastSyncTime;
	bool bReplicaVisible;
	float CurrentFadeAlpha;
#pragma endregion Synchro
	
	UPROPERTY()
	TObjectPtr<class UPlayerMovementComponent> CachedMovementComp;
	
	UPROPERTY()
	TObjectPtr<class UControlComponent> CachedControlComp;
	
	UPROPERTY()
	TObjectPtr<class UEquipmentComponent> CachedEquipmentComp;

public:
	UPROPERTY(BlueprintAssignable, Category = "Replica Events")
	FOnReplicaCreated OnReplicaCreated;
	
	UPROPERTY(BlueprintAssignable, Category = "Replica Events")
	FOnReplicaDestroyed OnReplicaDestroyed;
};
