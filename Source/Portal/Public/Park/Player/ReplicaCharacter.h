#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ReplicaCharacter.generated.h"

USTRUCT(BlueprintType)
struct FReplicaAnimationData
{
	GENERATED_BODY()

	// Movement Data
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float MovementSpeed = 0.0f;
	
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float NormalizedSpeed = 0.0f;
	
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	FVector2D MovementDirection = FVector2D::ZeroVector;
	
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bIsOnGround = true;
	
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bIsJumping = false;
	
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool bIsFalling = false;
	
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	float VerticalSpeed = 0.0f;
	
	// Equipment Data
	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	bool bHasWeapon = false;
	
	// Portal Gun Animation
	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	float WeaponBobIntensity = 0.0f;

	FReplicaAnimationData()
	{
		MovementSpeed = 0.0f;
		NormalizedSpeed = 0.0f;
		MovementDirection = FVector2D::ZeroVector;
		bIsOnGround = true;
		bIsJumping = false;
		bIsFalling = false;
		VerticalSpeed = 0.0f;
		bHasWeapon = false;
		WeaponBobIntensity = 0.0f;
	}
};


class UReplicaAnimInstance;

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
	void SetReplicaVisibility(bool bVisible);

	FORCEINLINE void SetSkeletalMesh(USkeletalMesh* SkeletalMesh) const
	{
		SkeletalMeshComp->SetSkeletalMesh(SkeletalMesh);
	}
	
	UFUNCTION(BlueprintPure, Category = "Replica")
	bool IsReplicaVisible() const { return bReplicaVisible; }
#pragma endregion Replica
	
#pragma region Anim
	UFUNCTION(BlueprintCallable, Category = "Anim")
	UAnimInstance* GetAnimInstance();
	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Sync")
	void OnAnimationDataUpdated(const FReplicaAnimationData& AnimData);
	UFUNCTION(BlueprintCallable, Category = "Animation Sync")
	void UpdateAnimationData(const FReplicaAnimationData& AnimData);
	
	UFUNCTION(BlueprintPure, Category = "Animation Data")
	const FReplicaAnimationData& GetAnimationData() const { return AnimationData; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Animation Sync")
	void OnPortalEffectTriggered(bool bEntering);
	UFUNCTION(BlueprintCallable, Category = "Portal Enter")
	void TriggerPortalEffect(bool bEntering);
#pragma endregion Anim

private:
#pragma region Replica
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category = "Replica Settings")
	bool bDisableCollisionOnSpawn;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category = "Replica Settings")
	bool bDisableInputOnSpawn;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category = "Replica Settings")
	bool bDisableMovementOnSpawn;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess), Category = "Replica Settings")
	bool bEnableShadowCasting;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Runtime State")
	bool bReplicaVisible;
#pragma endregion Replica

	
protected:
#pragma region Anim
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Animation Cache")
	FReplicaAnimationData AnimationData;
	
	UPROPERTY(EditDefaultsOnly, Category = "Anim Instance Ref")
	UReplicaAnimInstance* ReplicaAnimInstance;
#pragma endregion Anim

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComp;
	
	
private:	
	void SetupReplicaDefaults();
	void UpdateAnimInstanceProperties();
};
