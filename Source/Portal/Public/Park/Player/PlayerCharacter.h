// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/CharacterMovementComponent.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UCameraComponent;

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Character.h"

#include "PortalWeaponComponent.h"
#include "Park/ActorComponents/ControlComponent.h"
#include "Park/SceneComponents/PortalComponent.h"
#include "Park/RelatedPhysics/PlayerMovementComponent.h"
#include "Park/ActorComponents/EquipmentComponent.h"
#include "Park/ActorComponents/ReplicaSynchroComponent.h"


#include "PlayerCharacter.generated.h"

UCLASS()
class PORTAL_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	FName EquipmentName;
	
	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE USkeletalMeshComponent* GetSkeletalComp() const { return GetMesh(); }

	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE USkeletalMeshComponent* GetVisibleMeshComp() const { return VisibleSkeletalComp; }
	
	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE UControlComponent* GetControlComp() const { return ControlComp; }
	
	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE UEquipmentComponent* GetEquipmentComp() const { return EquipmentComp; }
	
	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE UCharacterMovementComponent* GetMovementComp() const { return GetCharacterMovement(); }
	//FORCEINLINE UPlayerMovementComponent* GetMovementComp() const { return MovementComp; }
	
	
	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE UReplicaSynchroComponent* GetReplicaSynchroComp() const { return ReplicaSynchroComp; }

	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE UPortalComponent* GetPortalComp() { return PortalComp; }

	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE UCameraComponent* GetCameraComp() { return CameraComp; }

protected:
	void SetupCamera();

	void SetupInvisibleMesh();
	void SetupVisibleMesh();
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UPortalComponent> PortalComp;
	UPROPERTY(EditDefaultsOnly, Category = Mesh, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> VisibleSkeletalComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UControlComponent> ControlComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UEquipmentComponent> EquipmentComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UCharacterMovementComponent> MovementComp;
	//TObjectPtr<UPlayerMovementComponent> MovementComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UReplicaSynchroComponent> ReplicaSynchroComp;
	
};
