// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UCapsuleComponent;
class UPortalComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UControlComponent;
class UEquipmentComponent;
class UPlayerMovementComponent;
class UReplicaSynchroComponent;

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"


#include "PlayerCharacter.generated.h"

UCLASS()
class PORTAL_API APlayerCharacter : public APawn
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
	FORCEINLINE USkeletalMeshComponent* GetSkeletalComp() const { return SkeletalComp; }
	
	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE UControlComponent* GetControlComp() const { return ControlComp; }
	
	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE UEquipmentComponent* GetEquipmentComp() const { return EquipmentComp; }
	
	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE UPlayerMovementComponent* GetMovementComp() const { return MovementComp; }
	
	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE UReplicaSynchroComponent* GetReplicaSynchroComp() const { return ReplicaSynchroComp; }

	UFUNCTION(BlueprintPure, Category = "Components")
	FORCEINLINE UPortalComponent* GetPortalComp() { return PortalComp; }
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UCapsuleComponent> CapsuleComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UPortalComponent> PortalComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> SkeletalComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UControlComponent> ControlComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UEquipmentComponent> EquipmentComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UPlayerMovementComponent> MovementComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess))
	TObjectPtr<UReplicaSynchroComponent> ReplicaSynchroComp;
	
};
