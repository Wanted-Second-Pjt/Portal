#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "ReplicaCharacter.generated.h"

UCLASS(BlueprintType, Blueprintable, Category = "Portal Game")
class PORTAL_API AReplicaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AReplicaCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	// for DeActivating
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Replica
	UFUNCTION(BlueprintCallable, Category = "Replica")
	void InitializeAsReplica();
	
	UFUNCTION(BlueprintCallable, Category = "Replica")
	void SetReplicaVisibility(bool bVisible, float FadeSpeed = 2.0f);
	
	UFUNCTION(BlueprintPure, Category = "Replica")
	bool IsReplicaVisible() const { return bReplicaVisible; }
	
	UFUNCTION(BlueprintCallable, Category = "Replica")
	void SetOpacityImmediate(float Opacity);
#pragma endregion Replica
	
#pragma region Anim
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Sync")
	void OnMovementDataUpdated(float MovementSpeed, const FVector2D& Direction, bool bOnGround);
	UFUNCTION(BlueprintCallable, Category = "Animation Sync")
	void UpdateMovementData(float MovementSpeed, const FVector2D& Direction, bool bOnGround);
	
	// temp. portal cant swap equipment
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Sync")
	void OnEquipmentStateChanged(bool bHasWeapon, int32 WeaponType);
	UFUNCTION(BlueprintCallable, Category = "Animation Sync")
	void UpdateEquipmentState(bool bHasWeapon, int32 WeaponType = 1);

	// Portal에 있던가..? delete
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Sync")
	void OnPortalEffectTriggered(bool bEntering);
	UFUNCTION(BlueprintCallable, Category = "Portal Effects")
	void TriggerPortalEffect(bool bEntering);
#pragma endregion Anim

protected:
#pragma region Replica
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Replica Settings")
	bool bDisableCollisionOnSpawn = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Replica Settings")
	bool bDisableInputOnSpawn = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Replica Settings")
	bool bDisableMovementOnSpawn = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Replica Settings")
	bool bEnableShadowCasting = true;
	
	//Material Fade.. use? - del
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Visual Effects")
	FName OpacityParameterName = TEXT("Opacity");
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Visual Effects")
	float DefaultFadeSpeed = 2.0f;

	// Replica Portal Interaction - del
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Portal Settings")
	bool bAutoHideDuringPortalTransition = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Portal Settings")
	float PortalTransitionFadeSpeed = 5.0f;
#pragma endregion Replica
	

private:
#pragma region Fade Effects // use..?
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Runtime State")
	float CurrentOpacity;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Runtime State")
	float TargetOpacity;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Runtime State")
	float FadeSpeed;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Runtime State")
	bool bIsFading;
#pragma endregion Fade Effects 

#pragma region Replica
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Runtime State")
	bool bReplicaVisible;
#pragma endregion Replica
	
#pragma region Anim
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Animation Cache")
	float CachedMovementSpeed;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Animation Cache")
	FVector2D CachedDirection;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Animation Cache")
	bool bCachedOnGround;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Animation Cache")
	bool bCachedHasWeapon;
#pragma endregion Anim

private:
	void ProcessFadeEffect(float DeltaTime);
	void ApplyOpacityToMaterials(float Opacity);
	void SetupReplicaDefaults();
};
